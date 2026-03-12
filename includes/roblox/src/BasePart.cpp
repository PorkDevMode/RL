#include "../BasePart.h"

bool RBX::BasePart::valid_class() const {
	if (!m_address || class_name() != "BasePart")
		return false;
	return true;
}

Vector3 RBX::BasePart::get_position() const {
	if (!this->valid_class())
		return {};

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return {};

	return mem.read<Vector3>(primitive + Offsets::Primitive::Position);
}

void RBX::BasePart::set_position(Vector3 pos) const {
	if (!valid_class())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	mem.write<Vector3>(primitive + Offsets::Primitive::Position, pos);
}

void RBX::BasePart::set_position(int axis, float value) const {
	if (!valid_class())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	uintptr_t position_addr = primitive + Offsets::Primitive::Position;

	switch (axis) {
	case 1:
		mem.write<float>(position_addr, value);
		break;
	case 2:
		mem.write<float>(position_addr + 0x4, value);
		break;
	case 3:
		mem.write<float>(position_addr + 0x8, value);
		break;
	default:
		break;
	}
}

Vector3 RBX::BasePart::get_rotation() const {
	if (!valid_class())
		return {};

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return {};

	return mem.read<Vector3>(m_address + Offsets::Primitive::Rotation);
}

void RBX::BasePart::set_rotation(Vector3 rotation) const {
	if (!valid_class())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	mem.write<Vector3>(m_address + Offsets::Primitive::Rotation, rotation);
}

void RBX::BasePart::set_rotation(int axis, float value) const {
	if (!valid_class())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	uintptr_t rotation_addr = primitive + Offsets::Primitive::Rotation;

	switch (axis) {
	case 1:
		mem.write<float>(rotation_addr, value);
		break;
	case 2:
		mem.write<float>(rotation_addr + 0x4, value);
		break;
	case 3:
		mem.write<float>(rotation_addr + 0x8, value);
		break;
	default:
		break;
	}
}