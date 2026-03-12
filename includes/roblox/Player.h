#pragma once

#include "Instance.h"

namespace RBX {
	class Player : public Instance {
	public:
		Player() = default;
		explicit Player(uintptr_t instance_address) : Instance(instance_address) {}
		RBX::Instance get_character() const;
		std::string get_display_name() const; // todo
		int get_uid() const; // todo
	private:
		bool class_valid() const;
	};
}