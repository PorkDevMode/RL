#pragma once

#include "Instance.h"

namespace RBX {
	class BasePart : public RBX::Instance {
	public:
		BasePart() = default;
		explicit BasePart(uintptr_t instance_address) : Instance(instance_address) {}
		Vector3 get_position() const;
		void set_position(Vector3 pos) const;
		void set_position(int axis, float value) const;

		Vector3 get_rotation() const;
		void set_rotation(Vector3 rotation) const;
		void set_rotation(int axis, float value) const;
	private:
		bool valid_class() const;
	};
}