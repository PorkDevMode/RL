#pragma once

#include "Instance.h"
#include <vector>

namespace RBX {
	class BasePart : public RBX::Instance {
	public:
		BasePart() = default;
		explicit BasePart(uintptr_t instance_address) : Instance(instance_address) {}

		Vector3 get_position() const;
		float get_position(Axis axis) const;
		void set_position(Vector3 pos) const;
		void set_position(Axis axis, float value) const;

		Vector3 get_rotation() const;
		void set_rotation(Vector3 rotation) const;
		void set_rotation(Axis axis, float value) const;
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
		mutable bool m_valid_class_name; // marked mutable so it isnt gay
	};
}
