#include <print>
#include <iostream>
#include "includes/memory/memory.h"
#include "includes/roblox/DataModel.h"
#include "includes/roblox/Players.h"
#include "includes/roblox/Humanoid.h"
#include "includes/roblox/BasePart.h"

void main_loop() {
	while (true) {
		if (RBX::DataModel::get().valid()) {

			std::this_thread::sleep_for(std::chrono::milliseconds(16));
			continue;
		}
	}
}

int main() {
	std::println("Starting");
	if (!mem.initialize("RobloxPlayerBeta.exe")) {
		std::println("Failed to initialize memory");
		return 1;
	}

	if (!RBX::VerifyVersion()) {
		std::println("Failed to initialize roblox, incorrect version");
		return 1;
	}

	RBX::DataModel::get().start();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	RBX::Players players = RBX::DataModel::get().find_first_child("Players").as<RBX::Players>();
	RBX::Player localplayer = players.get_local_player();
	RBX::Instance character = localplayer.get_character();
	RBX::Humanoid humanoid = character.find_first_child("Humanoid").as<RBX::Humanoid>();
	RBX::BasePart basepart = character.find_first_child("HumanoidRootPart").as<RBX::BasePart>();

	players.debug_print();
	localplayer.debug_print();
	character.debug_print();
	humanoid.debug_print();
	basepart.debug_print();

	float x {basepart.get_position(1)};
	float y {basepart.get_position(2)};
	float z {basepart.get_position(3)};
	std::cout << x;
	float wanted_position {x - 50};
	int count {0};
	while(x != wanted_position){
	    for (int i {}; i < 500; i++){
		basepart.set_position(1, wanted_position);
		basepart.set_position(3, z + 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	    }
	    x = basepart.get_position(1);
	    count++;
	}
	std::cout << count;
	std::cin.get();
}
