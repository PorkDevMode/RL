#include "../BasePart.h"
#include <cstdint>

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

uintptr_t RBX::BasePart::get_primitive() const {
	if (!valid_part())
		return 0;

	if (m_primitive)
		return m_primitive;

	m_primitive = mem.read<uintptr_t>(m_address + Offsets::BasePart::Primitive);
	return m_primitive;
}

uintptr_t RBX::BasePart::get_primitive_flags() const {
	if (!valid_part())
		return 0;

	if (m_primitive_flags)
		return m_primitive_flags;

	m_primitive_flags = mem.read<uintptr_t>(m_address + Offsets::Primitive::Flags);
	return m_primitive_flags;
}

bool RBX::BasePart::get_anchored() const {
	if (!valid_part())
		return false;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return false;

	uintptr_t primitive_flags = get_primitive_flags();
	if (!primitive_flags)
		return false;

	return mem.read<bool>(primitive_flags + Offsets::PrimitiveFlags::Anchored);
}

void RBX::BasePart::set_anchored(bool value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t primitive_flags = get_primitive_flags();
	if (!primitive_flags)
		return;

	mem.write<bool>(primitive_flags + Offsets::PrimitiveFlags::Anchored, value);
}

bool RBX::BasePart::get_can_collide() const {
	if (!valid_part())
		return false;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return false;

	uintptr_t primitive_flags = get_primitive_flags();
	if (!primitive_flags)
		return false;

	return mem.read<bool>(primitive_flags + Offsets::PrimitiveFlags::CanCollide);
}

void RBX::BasePart::set_can_collide(bool value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t primitive_flags = get_primitive_flags();
	if (!primitive_flags)
		return;

	mem.write<bool>(primitive_flags + Offsets::PrimitiveFlags::CanCollide, value);
}

bool RBX::BasePart::get_can_touch() const {
	if (!valid_part())
		return false;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return false;

	uintptr_t primitive_flags = get_primitive_flags();
	if (!primitive_flags)
		return false;

	return mem.read<bool>(primitive_flags + Offsets::PrimitiveFlags::CanTouch);
}

void RBX::BasePart::set_can_touch(bool value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t primitive_flags = get_primitive_flags();
	if (!primitive_flags)
		return;

	mem.write<bool>(primitive_flags + Offsets::PrimitiveFlags::CanTouch, value);
}

bool RBX::BasePart::get_cast_shadow() const {
	if (!valid_part())
		return false;
	return mem.read<bool>(m_address + Offsets::BasePart::CastShadow);
}

void RBX::BasePart::set_cast_shadow(bool value) const {
	if (!valid_part())
		return;
	mem.write<bool>(m_address + Offsets::BasePart::CastShadow, value);
}

bool RBX::BasePart::get_locked() const {
	if (!valid_part())
		return false;
	return mem.read<bool>(m_address + Offsets::BasePart::Locked);
}

void RBX::BasePart::set_locked(bool value) const {
	if (!valid_part())
		return;
	mem.write<bool>(m_address + Offsets::BasePart::Locked, value);
}

bool RBX::BasePart::get_massless() const {
	if (!valid_part())
		return false;
	return mem.read<bool>(m_address + Offsets::BasePart::Massless);
}

void RBX::BasePart::set_massless(bool value) const {
	if (!valid_part())
		return;
	mem.write<bool>(m_address + Offsets::BasePart::Massless, value);
}

float RBX::BasePart::get_reflectance() const {
	if (!valid_part())
		return 0.0f;
	return mem.read<float>(m_address + Offsets::BasePart::Reflectance);
}

void RBX::BasePart::set_reflectance(float value) const {
	if (!valid_part())
		return;
	mem.write<float>(m_address + Offsets::BasePart::Reflectance, value);
}

Material RBX::BasePart::get_material() const {
	if (!valid_part())
		return Material::Plastic;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return Material::Plastic;

	return static_cast<Material>(mem.read<int32_t>(primitive + Offsets::Primitive::Material));
}

void RBX::BasePart::set_material(Material material) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	mem.write<int32_t>(primitive + Offsets::Primitive::Material, static_cast<int32_t>(material));
}

PartType RBX::BasePart::get_part_type() const {
	if (!valid_part())
		return {};
	return static_cast<PartType>(mem.read<int32_t>(m_address + Offsets::BasePart::Shape));
}

void RBX::BasePart::set_part_type(PartType type) const {
	if (!valid_part())
		return;
	mem.write<int32_t>(m_address + Offsets::BasePart::Shape, static_cast<int32_t>(type));
}

Color3 RBX::BasePart::get_color() const {
	if (!valid_part())
		return {};
	return mem.read<Color3>(m_address + Offsets::BasePart::Color3);
}

void RBX::BasePart::set_color(Color3 color) const {
	if (!valid_part())
		return;
	mem.write<Color3>(m_address + Offsets::BasePart::Color3, color);
}

Vector3 RBX::BasePart::get_position() const {
	if (!valid_part())
		return {};

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return {};

	return mem.read<Vector3>(primitive + Offsets::Primitive::Position);
}

float RBX::BasePart::get_position(Axis axis) const {
	if (!valid_part())
		return 0.0f;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return 0.0f;

	uintptr_t position_addr = primitive + Offsets::Primitive::Position;

	switch (axis) {
	case Axis::X: return mem.read<float>(position_addr);
	case Axis::Y: return mem.read<float>(position_addr + 0x4);
	case Axis::Z: return mem.read<float>(position_addr + 0x8);
	default: break;
	}
	return 0.0f;
}

void RBX::BasePart::set_position(Vector3 pos) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	mem.write<Vector3>(primitive + Offsets::Primitive::Position, pos);
}

void RBX::BasePart::set_position(Axis axis, float value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t position_addr = primitive + Offsets::Primitive::Position;

	switch (axis) {
	case Axis::X: mem.write<float>(position_addr, value); break;
	case Axis::Y: mem.write<float>(position_addr + 0x4, value); break;
	case Axis::Z: mem.write<float>(position_addr + 0x8, value); break;
	default: break;
	}
}

Vector3 RBX::BasePart::get_rotation() const {
	if (!valid_part())
		return {};

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return {};

	return mem.read<Vector3>(primitive + Offsets::Primitive::Rotation);
}

float RBX::BasePart::get_rotation(Axis axis) const {
	if (!valid_part())
		return 0.0f;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return 0.0f;

	uintptr_t rotation_addr = primitive + Offsets::Primitive::Rotation;

	switch (axis) {
	case Axis::X: return mem.read<float>(rotation_addr);
	case Axis::Y: return mem.read<float>(rotation_addr + 0x4);
	case Axis::Z: return mem.read<float>(rotation_addr + 0x8);
	default: break;
	}
	return 0.0f;
}

void RBX::BasePart::set_rotation(Vector3 rotation) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	mem.write<Vector3>(primitive + Offsets::Primitive::Rotation, rotation);
}

void RBX::BasePart::set_rotation(Axis axis, float value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t rotation_addr = primitive + Offsets::Primitive::Rotation;

	switch (axis) {
	case Axis::X: mem.write<float>(rotation_addr, value); break;
	case Axis::Y: mem.write<float>(rotation_addr + 0x4, value); break;
	case Axis::Z: mem.write<float>(rotation_addr + 0x8, value); break;
	default: break;
	}
}

Vector3 RBX::BasePart::get_size() const {
	if (!valid_part())
		return {};

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return {};

	return mem.read<Vector3>(primitive + Offsets::Primitive::Size);
}

float RBX::BasePart::get_size(Axis axis) const {
	if (!valid_part())
		return 0.0f;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return 0.0f;

	uintptr_t size_addr = primitive + Offsets::Primitive::Size;

	switch (axis) {
	case Axis::X: return mem.read<float>(size_addr);
	case Axis::Y: return mem.read<float>(size_addr + 0x4);
	case Axis::Z: return mem.read<float>(size_addr + 0x8);
	default: break;
	}
	return 0.0f;
}

void RBX::BasePart::set_size(Vector3 size) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	mem.write<Vector3>(primitive + Offsets::Primitive::Size, size);
}

void RBX::BasePart::set_size(Axis axis, float value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t size_addr = primitive + Offsets::Primitive::Size;

	switch (axis) {
	case Axis::X: mem.write<float>(size_addr, value); break;
	case Axis::Y: mem.write<float>(size_addr + 0x4, value); break;
	case Axis::Z: mem.write<float>(size_addr + 0x8, value); break;
	default: break;
	}
}

Vector3 RBX::BasePart::get_assembly_angular_velocity() const {
	if (!valid_part())
		return {};

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return {};

	return mem.read<Vector3>(primitive + Offsets::Primitive::AssemblyAngularVelocity);
}

float RBX::BasePart::get_assembly_angular_velocity(Axis axis) const {
	if (!valid_part())
		return 0.0f;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return 0.0f;

	uintptr_t addr = primitive + Offsets::Primitive::AssemblyAngularVelocity;

	switch (axis) {
	case Axis::X: return mem.read<float>(addr);
	case Axis::Y: return mem.read<float>(addr + 0x4);
	case Axis::Z: return mem.read<float>(addr + 0x8);
	default: break;
	}
	return 0.0f;
}

void RBX::BasePart::set_assembly_angular_velocity(Vector3 value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	mem.write<Vector3>(primitive + Offsets::Primitive::AssemblyAngularVelocity, value);
}

void RBX::BasePart::set_assembly_angular_velocity(Axis axis, float value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t addr = primitive + Offsets::Primitive::AssemblyAngularVelocity;

	switch (axis) {
	case Axis::X: mem.write<float>(addr, value); break;
	case Axis::Y: mem.write<float>(addr + 0x4, value); break;
	case Axis::Z: mem.write<float>(addr + 0x8, value); break;
	default: break;
	}
}

Vector3 RBX::BasePart::get_assembly_linear_velocity() const {
	if (!valid_part())
		return {};

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return {};

	return mem.read<Vector3>(primitive + Offsets::Primitive::AssemblyLinearVelocity);
}

float RBX::BasePart::get_assembly_linear_velocity(Axis axis) const {
	if (!valid_part())
		return 0.0f;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return 0.0f;

	uintptr_t addr = primitive + Offsets::Primitive::AssemblyLinearVelocity;

	switch (axis) {
	case Axis::X: return mem.read<float>(addr);
	case Axis::Y: return mem.read<float>(addr + 0x4);
	case Axis::Z: return mem.read<float>(addr + 0x8);
	default: break;
	}
	return 0.0f;
}

void RBX::BasePart::set_assembly_linear_velocity(Vector3 value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	mem.write<Vector3>(primitive + Offsets::Primitive::AssemblyLinearVelocity, value);
}

void RBX::BasePart::set_assembly_linear_velocity(Axis axis, float value) const {
	if (!valid_part())
		return;

	uintptr_t primitive = get_primitive();
	if (!primitive)
		return;

	uintptr_t addr = primitive + Offsets::Primitive::AssemblyLinearVelocity;

	switch (axis) {
	case Axis::X: mem.write<float>(addr, value); break;
	case Axis::Y: mem.write<float>(addr + 0x4, value); break;
	case Axis::Z: mem.write<float>(addr + 0x8, value); break;
	default: break;
	}
}