#include "../Humanoid.h"
#include "includes/roblox/Offsets.h"
#include "includes/roblox/Structs.h"

bool RBX::Humanoid::class_valid() const {
    if (!m_address || class_name() != "Humanoid")
        return false;
    return true;
}

float RBX::Humanoid::get_walkspeed() const {
}

void RBX::Humanoid::set_walkspeed(float walkspeed) const {
    if (!class_valid())
        return;
    mem.write<int>(m_address + Offsets::Humanoid::WalkspeedCheck, walkspeed);
    mem.write<int>(m_address + Offsets::Humanoid::Walkspeed, walkspeed);
}

bool RBX::Humanoid::get_autojump() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::AutoJumpEnabled);
}

void RBX::Humanoid::set_autojump(bool value) const {
    if (!class_valid())
        return;
    mem.write<bool>(m_address + Offsets::Humanoid::AutoJumpEnabled, value);
}

bool RBX::Humanoid::get_evaluate_state_machine() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::EvaluateStateMachine);
}

void RBX::Humanoid::set_evaulate_state_machine(bool value) const {
    if (!class_valid())
        return;
    mem.read<bool>(m_address + Offsets::Humanoid::AutoJumpEnabled);
}


bool RBX::Humanoid::get_sit() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::Sit);
}

void RBX::Humanoid::set_sit(bool value) const {
    if (!class_valid())
        return;
    mem.write<bool>(m_address + Offsets::Humanoid::Sit, value);
}

bool RBX::Humanoid::get_platform_stand() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::PlatformStand);
}

void RBX::Humanoid::set_platform_stand(bool value) const {
    if (!class_valid())
        return;
    mem.write<bool>(m_address + Offsets::Humanoid::PlatformStand, value);
}

bool RBX::Humanoid::get_walking() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::IsWalking);
}

void RBX::Humanoid::set_walking(bool value) const {
    if (!class_valid())
        return;
    mem.write<bool>(m_address + Offsets::Humanoid::IsWalking, value);
}

bool RBX::Humanoid::get_requires_neck() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::RequiresNeck);
}

void RBX::Humanoid::set_requires_neck(bool value) const {
    if (!class_valid())
        return;
    mem.write<bool>(m_address + Offsets::Humanoid::RequiresNeck, value);
}

bool RBX::Humanoid::get_jump() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::Jump);
}

void RBX::Humanoid::set_jump() const {
    if (!class_valid())
        return;
    mem.write<bool>(m_address + Offsets::Humanoid::Jump, true);
}

bool RBX::Humanoid::get_auto_rotate() const {
    if (!class_valid())
        return false;
    return mem.read<bool>(m_address + Offsets::Humanoid::AutoRotate);
}

void RBX::Humanoid::set_auto_rotate(bool value) const {
    if (!class_valid())
        return;
    mem.write<bool>(m_address + Offsets::Humanoid::AutoRotate, value);
}

std::string RBX::Humanoid::get_display_name() const { // PORK
    if (!class_valid())
        return "";
    return mem.read_rstr(m_address + Offsets::Humanoid::DisplayName);
}

void RBX::Humanoid::set_display_name(std::string name) const {
    if (!class_valid())
        return;
    mem.write_rstr(m_address + Offsets::Humanoid::DisplayName, name);
}

DisplayDistanceType RBX::Humanoid::get_display_distance_type() const {
    if (!class_valid())
        return DisplayDistanceType::None;
    return static_cast<DisplayDistanceType>(mem.read<int32_t>(m_address + Offsets::Humanoid::DisplayDistanceType));
}

void RBX::Humanoid::set_display_distance_type(DisplayDistanceType type) const {
    if (!class_valid())
        return;
    mem.write<int32_t>(m_address + Offsets::Humanoid::DisplayDistanceType, static_cast<int32_t>(type));
}

HumanoidStateType RBX::Humanoid::get_humanoid_state() const {
    if (!class_valid())
        return HumanoidStateType::None;
    uintptr_t state_ptr = mem.read<uintptr_t>(m_address + Offsets::Humanoid::HumanoidState);
    return static_cast<HumanoidStateType>(mem.read<int32_t>(state_ptr + Offsets::Humanoid::HumanoidStateID));
}

void RBX::Humanoid::set_humanoid_state(HumanoidStateType type) const {
    if (!class_valid())
        return;
    uintptr_t state_ptr = mem.read<uintptr_t>(m_address + Offsets::Humanoid::HumanoidState);
    mem.write<int32_t>(state_ptr + Offsets::Humanoid::HumanoidStateID, static_cast<int32_t>(type));
}

NameOcclusion RBX::Humanoid::get_name_occlusion() const {
    if (!class_valid())
        return NameOcclusion::NoOcclusion;
    return static_cast<NameOcclusion>(mem.read<int32_t>(m_address + Offsets::Humanoid::NameOcclusion));
}

void RBX::Humanoid::set_name_occlusion(NameOcclusion occlusion) const {
    if (!class_valid())
        return;
    mem.write<int32_t>(m_address + Offsets::Humanoid::NameOcclusion, static_cast<int32_t>(occlusion));
}

HumanoidRigType RBX::Humanoid::get_rig_type() const {
    if (!class_valid())
        return HumanoidRigType::None;
    return static_cast<HumanoidRigType>(mem.read<int32_t>(m_address + Offsets::Humanoid::RigType));
}

void RBX::Humanoid::set_rig_type(HumanoidRigType type) const {
    if (!class_valid())
        return;
    mem.write<int32_t>(m_address + Offsets::Humanoid::RigType, static_cast<int32_t>(type));
}

HealthDisplayType RBX::Humanoid::get_health_display_type() const {
    if (!class_valid())
        return HealthDisplayType::AlwaysOff;
    return static_cast<HealthDisplayType>(mem.read<int32_t>(m_address + Offsets::Humanoid::HealthDisplayType));
}

void RBX::Humanoid::set_health_display_type(HealthDisplayType type) const {
    if (!class_valid())
        return;
    mem.write<int32_t>(m_address + Offsets::Humanoid::HealthDisplayType, static_cast<int32_t>(type));
}

RBX::Instance RBX::Humanoid::get_seat_part() const { // PORK
    if (!class_valid())
        return {};
    return RBX::Instance(mem.read<uintptr_t>(m_address + Offsets::Humanoid::SeatPart));
}

void RBX::Humanoid::set_seat_part(const RBX::Instance& instance) const {
    if (!class_valid() || !instance)
        return;
    mem.write<uintptr_t>(m_address + Offsets::Humanoid::SeatPart, instance.address());
}

RBX::Instance RBX::Humanoid::get_humanoid_root_part() const { // PORK
    if (!class_valid())
        return {};
    return RBX::Instance(mem.read<uintptr_t>(m_address + Offsets::Humanoid::HumanoidRootPart));
}

void RBX::Humanoid::set_humanoid_root_part(const RBX::Instance& instance) const {
    if (!class_valid() || !instance)
        return;
    mem.write<uintptr_t>(m_address + Offsets::Humanoid::HumanoidRootPart, instance.address());
}

Vector3 RBX::Humanoid::get_camera_offset() const {
    if (!class_valid())
        return {};
    return mem.read<Vector3>(m_address + Offsets::Humanoid::CameraOffset);
}

void RBX::Humanoid::set_camera_offset(Vector3 offset) const {
    if (!class_valid())
        return;
    mem.write<Vector3>(m_address + Offsets::Humanoid::CameraOffset, offset);
}

Material RBX::Humanoid::get_floor_material() const { // PORK
    if (!class_valid())
        return Material::Plastic;
    return static_cast<Material>(mem.read<int32_t>(m_address + Offsets::Humanoid::FloorMaterial));
}

void RBX::Humanoid::set_floor_material(Material material) const {
    if (!class_valid())
        return;
    mem.write<int32_t>(m_address + Offsets::Humanoid::FloorMaterial, static_cast<int32_t>(material));
}

float RBX::Humanoid::get_hipheight() const {
    if (!class_valid())
        return 0.0f;
    return mem.read<float>(m_address + Offsets::Humanoid::HipHeight);
}

void RBX::Humanoid::set_hipheight(float value) const {
    if (!class_valid())
        return;
    mem.write<float>(m_address + Offsets::Humanoid::HipHeight, value);
}

float RBX::Humanoid::get_health() const {
    if (!class_valid())
        return 0.0f;
    return mem.read<float>(m_address + Offsets::Humanoid::Health);
}

void RBX::Humanoid::set_health(float value) const {
    if (!class_valid())
        return;
    mem.write<float>(m_address + Offsets::Humanoid::Health, value);
}

float RBX::Humanoid::get_max_health() const {
    if (!class_valid())
        return 0.0f;
    return mem.read<float>(m_address + Offsets::Humanoid::MaxHealth);
}

void RBX::Humanoid::set_max_health(float value) const {
    if (!class_valid())
        return;
    mem.write<float>(m_address + Offsets::Humanoid::MaxHealth, value);
}

float RBX::Humanoid::get_max_slope_angle() const {
    if (!class_valid())
        return 0.0f;
    return mem.read<float>(m_address + Offsets::Humanoid::MaxSlopeAngle);
}

void RBX::Humanoid::set_max_slope_angle(float value) const {
    if (!class_valid())
        return;
    mem.write<float>(m_address + Offsets::Humanoid::MaxSlopeAngle, value);
}

float RBX::Humanoid::get_jump_height() const {
    if (!class_valid())
        return 0.0f;
    return mem.read<float>(m_address + Offsets::Humanoid::JumpHeight);
}

void RBX::Humanoid::set_jump_height(float value) const {
    if (!class_valid())
        return;
    mem.write<float>(m_address + Offsets::Humanoid::JumpHeight, value);
}

float RBX::Humanoid::get_jump_power() const {
    if (!class_valid())
        return 0.0f;
    return mem.read<float>(m_address + Offsets::Humanoid::JumpPower);
}

void RBX::Humanoid::set_jump_power(float value) const {
    if (!class_valid())
        return;
    mem.write<float>(m_address + Offsets::Humanoid::JumpPower, value);
}

float RBX::Humanoid::get_health_display_distance() const {
    if (!class_valid())
        return 0.0f;
    return mem.read<float>(m_address + Offsets::Humanoid::HealthDisplayDistance);
}

void RBX::Humanoid::set_health_display_distance(float value) const {
    if (!class_valid())
        return;
    mem.write<float>(m_address + Offsets::Humanoid::HealthDisplayDistance, value);
}