#include "../BasePart.h"

bool RBX::BasePart::valid_part() const {
	if (!m_address)
		return false;

	if (m_valid_class_name)
		return true;

	for (const std::string& str : m_valid_class_names) {
		if (class_name() == str) {
			m_valid_class_name = true;
			return true;
		}
	}

	return false;
}

Vector3 RBX::BasePart::get_position() const {
	if (!valid_part())
		return {};

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return {};

	return mem.read<Vector3>(primitive + Offsets::Primitive::Position);
}

float RBX::BasePart::get_position(Axis axis) const {
	if (!valid_part())
		return 0.0f;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return 0.0f;

	uintptr_t position_addr = primitive + Offsets::Primitive::Position;

	switch (axis) {
	case Axis::X:
		return mem.read<float>(position_addr);
	case Axis::Y:
		return mem.read<float>(position_addr + 0x4);
	case Axis::Z:
		return mem.read<float>(position_addr + 0x8);
	default:
		break;
	}
    return 0.0f;
}

void RBX::BasePart::set_position(Vector3 pos) const {
	if (!valid_part())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	mem.write<Vector3>(primitive + Offsets::Primitive::Position, pos);
}

void RBX::BasePart::set_position(Axis axis, float value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	uintptr_t position_addr = primitive + Offsets::Primitive::Position;

	switch (axis) {
	case Axis::X:
		mem.write<float>(position_addr, value);
		break;
	case Axis::Y:
		mem.write<float>(position_addr + 0x4, value);
		break;
	case Axis::Z:
		mem.write<float>(position_addr + 0x8, value);
		break;
	default:
		break;
	}
}

Vector3 RBX::BasePart::get_rotation() const {
	if (!valid_part())
		return {};

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return {};

	return mem.read<Vector3>(m_address + Offsets::Primitive::Rotation);
}

void RBX::BasePart::set_rotation(Vector3 rotation) const {
	if (!valid_part())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	mem.write<Vector3>(m_address + Offsets::Primitive::Rotation, rotation);
}

void RBX::BasePart::set_rotation(Axis axis, float value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	if (!primitive)
		return;

	uintptr_t rotation_addr = primitive + Offsets::Primitive::Rotation;

	switch (axis) {
	case Axis::X:
		mem.write<float>(rotation_addr, value);
		break;
	case Axis::Y:
		mem.write<float>(rotation_addr + 0x4, value);
		break;
	case Axis::Z:
		mem.write<float>(rotation_addr + 0x8, value);
		break;
	default:
		break;
	}
}
