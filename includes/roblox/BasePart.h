#pragma once

#include "Instance.h"
#include <vector>

namespace RBX {
	class BasePart : public RBX::Instance {
	public:
		BasePart() = default;
		explicit BasePart(uintptr_t instance_address) : Instance(instance_address) {}

		bool get_anchored() const;
		void set_anchored(bool value) const;

		bool get_can_collide() const;
		void set_can_collide(bool value) const;

		bool get_can_touch() const;
		void set_can_touch(bool value) const;

		bool get_cast_shadow() const;
		void set_cast_shadow(bool value) const;

		bool get_locked() const;
		void set_locked(bool value) const;

		bool get_massless() const;
		void set_massless(bool value) const;

		float get_reflectance() const;
		void set_reflectance(float value) const;

		Material get_material() const;
		void set_material(Material material) const;

		PartType get_part_type() const;
		void set_part_type(PartType type) const;

		Color3 get_color() const;
		void set_color(Color3 color) const;

		Vector3 get_position() const;
		float get_position(Axis axis) const;
		void set_position(Vector3 pos) const;
		void set_position(Axis axis, float value) const;

		Vector3 get_rotation() const;
		float get_rotation(Axis axis) const;
		void set_rotation(Vector3 rotation) const;
		void set_rotation(Axis axis, float value) const;

		Vector3 get_size() const;
		float get_size(Axis axis) const;
		void set_size(Vector3 size) const;
		void set_size(Axis axis, float value) const;

		Vector3 get_assembly_angular_velocity() const;
		float get_assembly_angular_velocity(Axis axis) const;
		void set_assembly_angular_velocity(Vector3 value) const;
		void set_assembly_angular_velocity(Axis axis, float value) const;

		Vector3 get_assembly_linear_velocity() const;
		float get_assembly_linear_velocity(Axis axis) const;
		void set_assembly_linear_velocity(Vector3 value) const;
		void set_assembly_linear_velocity(Axis axis, float value) const;
	protected:
		bool valid_part() const;
	private:
		const std::vector<std::string> m_valid_class_names = {
			"Part",
			"MeshPart",
			"CornerWedgePart",
			"WedgePart",
			"TrussPart",
			"VehicleSeat",
			"Seat",
			"SpawnLocation",
			"Platform",
			"SkateboardPlatform",
			"FlagStand",
			"UnionOperation",
			"NegateOperation",
		};
		mutable bool m_valid_class_name = false;

		uintptr_t get_primitive() const;
		uintptr_t get_primitive_flags() const;

		mutable uintptr_t m_primitive = 0;
		mutable uintptr_t m_primitive_flags = 0;
	};
}