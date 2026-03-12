#include "../Humanoid.h"

bool RBX::Humanoid::class_valid() const {
    if (!m_address||class_name()!="Humanoid")
	return false;
    return true;
}

void RBX::Humanoid::set_walkspeed(float walkspeed) const {
    if (!class_valid())
	return;
    mem.write<float>(m_address + Offsets::Humanoid::WalkspeedCheck, walkspeed);
    mem.write<float>(m_address + Offsets::Humanoid::Walkspeed, walkspeed);
}
