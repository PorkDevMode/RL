#pragma once

#include "Instance.h"
#include "Player.h"

namespace RBX {
	class Players : public Instance {
	public:
		Players() = default;
		explicit Players(uintptr_t instance_address) : Instance(instance_address) {}
		RBX::Player get_local_player() const;
	private:
		bool class_valid() const;
	};
}