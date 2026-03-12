#pragma once

#include <string>
#include <vector>
#include <regex>
#include <thread>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <windows.h>
#include <print>

#include "includes/memory/memory.h"
#include "offsets.h"

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Vector2 {
    float x;
    float y;
};

namespace Roblox {
    inline std::thread gDatamodelUpdateThread;
    inline bool gRunning = true;
    inline bool gRobloxConfigured = false;
    inline bool gEsp = true;
    inline bool gShouldUpdateDatamodel = true;

    class Instance {
    protected:
        uintptr_t get_primitive_pointer(uintptr_t offset) const {
            if (!address)
                return 0;
            return mem.read<uintptr_t>(address + offset);
        }

    public:
        uintptr_t address = 0;
        std::string name;
        std::string class_name;
        bool valid_instance = false;

        explicit operator bool() const {
            return is_valid();
        }

        bool initialize(uintptr_t addr) {
            if (!addr || !mem.initialized)
                return false;

            address = addr;
            class_name = get_class_name();
            name = get_name();
            valid_instance = !class_name.empty();

            return valid_instance;
        }

        bool is_valid() const {
            return !get_class_name().empty() && valid_instance;
        }

        std::string get_name() const {
            if (!address)
                return "";

            uintptr_t name_ptr = mem.read<uintptr_t>(address + Offsets::Instance::Name);
            if (!name_ptr)
                return "";

            return mem.read_rstr(name_ptr);
        }

        void set_name(const std::string& str) const {
            if (!is_valid())
                return;

            uintptr_t name_ptr = mem.read<uintptr_t>(address + Offsets::Instance::Name);
            if (name_ptr)
                mem.write_rstr(name_ptr, str);
        }

        std::string get_class_name() const {
            if (!address)
                return "";

            uintptr_t class_name_ptr = mem.read<uintptr_t>(address + Offsets::Instance::ClassDescriptor);
            if (!class_name_ptr)
                return "";

            uintptr_t class_name_str_ptr = mem.read<uintptr_t>(class_name_ptr + Offsets::Instance::ClassName);
            if (!class_name_str_ptr)
                return "";

            return mem.read_rstr(class_name_str_ptr);
        }

        template<typename T = Instance>
        std::vector<T> get_children() const {
            std::vector<T> buffer;
            if (!address)
                return buffer;

            uintptr_t children_struct_ptr = mem.read<uintptr_t>(address + Offsets::Instance::ChildrenStart);
            if (!children_struct_ptr)
                return buffer;

            uintptr_t children_start = mem.read<uintptr_t>(children_struct_ptr);
            uintptr_t children_end = mem.read<uintptr_t>(children_struct_ptr + Offsets::Instance::ChildrenEnd);

            while (children_start && children_start != children_end) {
                uintptr_t child_address = mem.read<uintptr_t>(children_start);
                if (!child_address)
                    break;

                T child;
                if (child.initialize(child_address))
                    buffer.push_back(std::move(child));

                children_start += 0x10;
            }

            return buffer;
        }

        std::vector<uintptr_t> get_children_address() const {
            std::vector<uintptr_t> buffer;
            if (!address)
                return buffer;

            uintptr_t children_struct_ptr = mem.read<uintptr_t>(address + Offsets::Instance::ChildrenStart);
            if (!children_struct_ptr)
                return buffer;

            uintptr_t children_start = mem.read<uintptr_t>(children_struct_ptr);
            uintptr_t children_end = mem.read<uintptr_t>(children_struct_ptr + Offsets::Instance::ChildrenEnd);

            while (children_start && children_start != children_end) {
                uintptr_t child_address = mem.read<uintptr_t>(children_start);
                if (child_address)
                    buffer.push_back(children_start);

                children_start += 0x10;
            }

            return buffer;
        }

        template<typename T = Instance>
        T find_first_child(const std::string& target_name) const {
            for (const auto& child : get_children()) {
                if (child.name == target_name) {
                    T result;
                    result.initialize(child.address);
                    return result;
                }
            }
            return {};
        }

        template<typename T = Instance>
        T find_first_child_path(const std::string& path) const {
            std::vector<std::string> parts;
            std::stringstream ss(path);
            std::string part;

            while (std::getline(ss, part, '.'))
                parts.push_back(part);

            if (parts.empty())
                return {};

            Instance current;
            current.initialize(this->address);

            for (const auto& target_name : parts) {
                bool found = false;

                for (const auto& child : current.get_children()) {
                    if (child.name == target_name) {
                        current.initialize(child.address);
                        found = true;
                        break;
                    }
                }

                if (!found)
                    return {};
            }

            T result;
            result.initialize(current.address);
            return result;
        }

        uintptr_t find_first_child_address(const std::string& target_name) const {
            for (const auto& child_addr : get_children_address()) {
                uintptr_t child_ptr = mem.read<uintptr_t>(child_addr);
                Instance child_i;
                if (child_i.initialize(child_ptr) && child_i.name == target_name)
                    return child_addr;
            }
            return 0;
        }

        void set_parent(const Instance& new_parent) const {
            if (address)
                mem.write<uintptr_t>(address + Offsets::Instance::Parent, new_parent.address);
        }

        void set_parent(uintptr_t parent_address) const {
            if (address)
                mem.write<uintptr_t>(address + Offsets::Instance::Parent, parent_address);
        }

        Instance get_parent() const {
            Instance p;
            if (address) {
                uintptr_t parent_ptr = mem.read<uintptr_t>(address + Offsets::Instance::Parent);
                p.initialize(parent_ptr);
            }
            return p;
        }

        void remove() const {
            if (address)
                set_parent(0);
        }
    };

    class Part : public Instance {
    public:
        Vector3 get_position() const {
            if (!address)
                return {};

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (!prim_ptr)
                return {};

            return mem.read<Vector3>(prim_ptr + Offsets::Primitive::Position);
        }

        float get_position(int axis) const {
            if (!address)
                return 0.0f;

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (!prim_ptr)
                return 0.0f;

            switch (axis) {
            case 1:
                return mem.read<float>(prim_ptr + Offsets::Primitive::Position + 0x4);
            case 2:
                return mem.read<float>(prim_ptr + Offsets::Primitive::Position + 0x8);
            case 3:
                return mem.read<float>(prim_ptr + Offsets::Primitive::Position + 0xc);
            default:
                return 0.0f;
            }
        }

        void set_position(const Vector3& value) const {
            if (!address)
                return;

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (prim_ptr)
                mem.write<Vector3>(prim_ptr + Offsets::Primitive::Position, value);
        }

        void set_position(float value, int axis) const {
            if (!address)
                return;

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (!prim_ptr)
                return;

            switch (axis) {
                case 1:
                    mem.write<float>(prim_ptr + Offsets::Primitive::Position + 0x4, value);
                    break;
                case 2:
                    mem.write<float>(prim_ptr + Offsets::Primitive::Position + 0x8, value);
                    break;
                case 3:
                    mem.write<float>(prim_ptr + Offsets::Primitive::Position + 0xc, value);
                    break;
                default: {
                    break;
                }
            }
        }

        void set_rotation(const Vector3& value) const {
            if (!address)
                return;

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (prim_ptr)
                mem.write<Vector3>(prim_ptr + Offsets::Primitive::Rotation , value);
        }

        Vector3 get_velocity() const {
            if (!is_valid())
                return {};

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (!prim_ptr)
                return {};

            return mem.read<Vector3>(prim_ptr + Offsets::Primitive::AssemblyLinearVelocity);
        }

        void set_velocity(const Vector3& value) const {
            if (!is_valid())
                return;

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (prim_ptr) {
                mem.write<Vector3>(prim_ptr + Offsets::Primitive::AssemblyLinearVelocity, value);
                mem.write<Vector3>(prim_ptr + Offsets::Primitive::AssemblyAngularVelocity, value);
            }
        }

        void set_velocity(float value, int axis) const {
            if (!is_valid())
                return;

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            if (!prim_ptr)
                return;

            switch (axis) {
                case 1:
                    mem.write<float>(prim_ptr + Offsets::Primitive::AssemblyLinearVelocity, value);
                    break;
                case 2:
                    mem.write<float>(prim_ptr + Offsets::Primitive::AssemblyLinearVelocity + 0x4, value);
                    break;
                case 3:
                    mem.write<float>(prim_ptr + Offsets::Primitive::AssemblyLinearVelocity + 0x8, value);
                    break;
                default: {
                    break;
                }
            }
        }

        void set_collision(bool value) const {
            if (!is_valid())
                return;

            uintptr_t prim_ptr = get_primitive_pointer(Offsets::BasePart::Primitive);
            uintptr_t prim_flags = mem.read<uintptr_t>(prim_ptr + Offsets::Primitive::Flags);
            if (prim_flags)
                mem.write<byte>(prim_flags + Offsets::PrimitiveFlags::CanCollide, static_cast<byte>(value));
        }
    };

    class Camera : public Instance {
    public:
        Vector3 get_position() const {
            if (!address)
                return {};
            return mem.read<Vector3>(address + Offsets::Camera::Position);
        }

        void set_position(const Vector3& value) const {
            if (!address)
                return;
            mem.write<Vector3>(address + Offsets::Camera::Position, value);
        }
    };

    class Humanoid : public Instance {
    public:
        float get_walkspeed() const {
            if (!is_valid())
                return 0.0f;
            return mem.read<float>(address + Offsets::Humanoid::Walkspeed);
        }

        void set_walkspeed(float value) const {
            if (!is_valid())
                return;

            mem.write<float>(address + Offsets::Humanoid::Walkspeed, value);
            mem.write<float>(address + Offsets::Humanoid::WalkspeedCheck, value);
        }

        void move_to_part(Part part, bool wait) {
            mem.write<uintptr_t>(this->address + Offsets::Humanoid::MoveToPart, part.address);
            Vector3 part_pos = part.get_position();
            move_to_pos(part_pos, wait);
        }
    private:
        void move_to_pos(Vector3 pos, bool wait) {
            Instance character = this->get_parent();
            std::println("Character: {:#x}", character.address);
            Part hrp = character.find_first_child<Part>("HumanoidRootPart");
            Vector3 current_pos = hrp.get_position();

            if (wait) {
                execute_move(hrp, pos);
            }
            else {
                //move_thread = std::thread(execute_move);
            }
        }

        void execute_move(Part hrp, Vector3 pos) {
            while (true) {
                Vector3 current_pos = hrp.get_position();
                if (abs(current_pos.x - pos.x) <= 1.0f && abs(current_pos.z - pos.z) <= 1.0f) {
                    break;
                }

                mem.write<Vector3>(this->address + Offsets::Humanoid::MoveToPoint, pos);
                mem.write<bool>(this->address + Offsets::Humanoid::IsWalking, true);
                //std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    };

    class Player : public Instance {
    public:
        Instance get_character() const {
            if (!is_valid())
                return {};

            uintptr_t found_char = mem.read<uintptr_t>(address + Offsets::Player::ModelInstance);
            if (!found_char)
                return {};

            Instance char_instance;
            char_instance.initialize(found_char);
            return char_instance;
        }

        int get_user_id() const {
            if (!is_valid())
                return 0;

            return mem.read<int>(address + Offsets::Player::UserId);
        }

        void set_user_id(int uid) const {
            if (!is_valid())
                return;

            mem.write<int>(address + Offsets::Player::UserId, uid);
        }
    };

    class Players : public Instance {
    public:
        Player get_local_player() const {
            if (!is_valid())
                return {};

            uintptr_t found_lp = mem.read<uintptr_t>(address + Offsets::Player::LocalPlayer);
            if (!found_lp)
                return {};

            Player lp_instance;
            lp_instance.initialize(found_lp);
            return lp_instance;
        }
    };

    class Model : public Instance {};

    class Datamodel : public Instance {
    public:
        bool loaded() {
            if (!is_valid())
                return false;
            return mem.read<uintptr_t>(address + Offsets::DataModel::GameLoaded);
        }
    };

    inline Datamodel gDatamodel;

    inline bool GetDatamodel() {
        if (!mem.initialized)
            return false;

        uintptr_t datamodel_fake = mem.read<uintptr_t>(mem.process_info.base + Offsets::FakeDataModel::Pointer);
        uintptr_t datamodel_real = mem.read<uintptr_t>(datamodel_fake + Offsets::FakeDataModel::RealDataModel);

        Datamodel found_datamodel;
        if (!found_datamodel.initialize(datamodel_real))
            return false;

        if (found_datamodel.class_name != "DataModel" ||
            !mem.read<uintptr_t>(found_datamodel.address + Offsets::DataModel::Workspace) ||
            found_datamodel.get_name() != "Ugc")
            return false;

        gDatamodel = found_datamodel;
        uintptr_t place_id = mem.read<uintptr_t>(gDatamodel.address + Offsets::DataModel::PlaceId);
        std::println("connected to place: {}", place_id);
        return true;
    }

    inline void UpdateDatamodel() {
        while (gRunning) {
            if (!gShouldUpdateDatamodel) {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                continue;
            }

            if (!gDatamodel.address ||
                gDatamodel.get_class_name() != "DataModel" ||
                !mem.read<uintptr_t>(gDatamodel.address + Offsets::DataModel::Workspace) ||
                gDatamodel.get_name() != "Ugc") {

                gRobloxConfigured = false;
                gDatamodel = {};

                if (GetDatamodel()) {
                    gRobloxConfigured = true;
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    std::println("Found datamodel");
                    continue;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    inline void StartDatamodelThread() {
        gDatamodelUpdateThread = std::thread(UpdateDatamodel);
        gDatamodelUpdateThread.detach();
    }

    inline bool VerifyVersion() {
        char buffer[MAX_PATH];
        DWORD size = MAX_PATH;

        if (!QueryFullProcessImageNameA(mem.process_info.process_handle, 0, buffer, &size))
            return false;

        std::string version(buffer, size);
        std::regex version_regex(R"(version-[a-f0-9]+)", std::regex_constants::icase);
        std::smatch match;

        if (!std::regex_search(version, match, version_regex))
            return false;

        version = match.str();
        std::println("current version is: {}", version);

        if (version != Offsets::ClientVersion) {
            std::println("version mismatch, wanted version is: {}", Offsets::ClientVersion);
            return false;
        }

        return true;
    }
}