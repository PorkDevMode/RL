#include "../Humanoid.h"
#include "includes/roblox/Offsets.h"

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

}

void RBX::Humanoid::set_display_name(std::string name) const {

}

DisplayDistanceType RBX::Humanoid::get_display_distance_type() const {

}

void RBX::Humanoid::set_display_distance_type(DisplayDistanceType type) const {

}

HumanoidStateType RBX::Humanoid::get_humanoid_state() const {

}

void RBX::Humanoid::set_humanoid_state(HumanoidStateType type) const {
}

NameOcclusion RBX::Humanoid::get_name_occlusion() const {

}

void RBX::Humanoid::set_name_occlusion(NameOcclusion occlusion) const {

}

HumanoidRigType RBX::Humanoid::get_rig_type() const {

}

void RBX::Humanoid::set_rig_type(HumanoidRigType type) const {

}

HealthDisplayType RBX::Humanoid::get_health_display_type() const {

}

void RBX::Humanoid::set_health_display_type(HealthDisplayType type) const {

}

RBX::Instance RBX::Humanoid::get_seat_part() const { // PORK

}

void RBX::Humanoid::set_seat_part(const RBX::Instance& instance) const {

}

RBX::Instance RBX::Humanoid::get_humanoid_root_part() const { // PORK

}

void RBX::Humanoid::set_humanoid_root_part(const RBX::Instance& instance) const {

}

Vector3 RBX::Humanoid::get_camera_offset() const {

}

void RBX::Humanoid::set_camera_offset(Vector3 offset) const {

}

Material RBX::Humanoid::get_floor_material() const { // PORK

}

void RBX::Humanoid::set_floor_material(Material material) const {

}

float RBX::Humanoid::get_hipheight() const {

}

void RBX::Humanoid::set_hipheight(float value) const {

}

float RBX::Humanoid::get_health() const {

}

void RBX::Humanoid::set_health(float value) const {

}

float RBX::Humanoid::get_max_health() const {

}

void RBX::Humanoid::set_max_health(float value) const {

}

float RBX::Humanoid::get_max_slope_angle() const {

}

void RBX::Humanoid::set_max_slope_angle(float value) const {

}

float RBX::Humanoid::get_jump_height() const {

}

void RBX::Humanoid::set_jump_height(float value) const {

}

float RBX::Humanoid::get_jump_power() const {

}

void RBX::Humanoid::set_jump_power(float value) const {

}

float RBX::Humanoid::get_health_display_distance() const {

}

void RBX::Humanoid::set_health_display_distance(float value) const {
    
}