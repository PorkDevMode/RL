#include "../Player.h"

bool RBX::Player::class_valid() const {
	if (!m_address || class_name() != "Player")
		return false;
	return true;
}

RBX::Instance RBX::Player::get_character() const {
	if (!class_valid())
		return {};
	return RBX::Instance(mem.read<uintptr_t>(m_address + Offsets::Player::ModelInstance));
}