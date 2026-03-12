#include "../Players.h"

RBX::Player RBX::Players::get_local_player() const {
	if (!class_valid())
		return {};

	return RBX::Player(mem.read<uintptr_t>(m_address + Offsets::Player::LocalPlayer));
}

bool RBX::Players::class_valid() const {
	if (!m_address || class_name() != "Players")
		return false;
	return true;
}