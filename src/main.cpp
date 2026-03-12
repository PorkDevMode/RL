#include <print>
#include <iostream>
#include "includes/memory/memory.h"
#include "includes/roblox/DataModel.h"
#include "includes/roblox/Players.h"

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

	players.debug_print();
	localplayer.debug_print();
	character.debug_print();

	std::cin.get();
}
