#include "../Humanoid.h"

bool RBX::Humanoid::class_valid() const {
    if (!m_address||class_name()!="Humanoid")
	    return false;
    return true;
}

void RBX::Humanoid::set_walkspeed(float walkspeed) const {
    if (!class_valid())
<<<<<<< HEAD
	return;
    mem.write<float>(m_address + Offsets::Humanoid::WalkspeedCheck, walkspeed);
    mem.write<float>(m_address + Offsets::Humanoid::Walkspeed, walkspeed);
=======
	    return;
    mem.write<int>(m_address + Offsets::Humanoid::WalkspeedCheck, walkspeed);
    mem.write<int>(m_address + Offsets::Humanoid::Walkspeed, walkspeed);
>>>>>>> 895b24ef88816d4bc9043b3873c0441dbd2d2e8e
}
