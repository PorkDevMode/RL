#pragma once

#include "Instance.h"

namespace RBX {
	class BasePart : public RBX::Instance { // basepart is inherited by many classes it is not its own specific class, TODO: make it inheritable and scalable
	public:
		BasePart() = default;
		explicit BasePart(uintptr_t instance_address) : Instance(instance_address) {}
		Vector3 get_position() const;
		float get_position(Axis axis) const;
		void set_position(Vector3 pos) const;
		void set_position(Axis axis, float value) const;

		Vector3 get_rotation() const;
		void set_rotation(Vector3 rotation) const;
		void set_rotation(int axis, float value) const;
	private:
		bool valid_class() const; // TODO: need to verify many class names here
	};
}
