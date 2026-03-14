#pragma once

#include <cstdint>
#include <vector>

struct Vector3 {
	float x, y, z;
};

struct Vector2 {
	float x, y;
};

enum HumanoidStateType {
	FallingDown = 0,
	Ragdoll = 1,
	GettingUp = 2,
	Jumping = 3,
	Swimming = 4,
	Freefall = 5,
	Flying = 6,
	Landed = 7,
	Running = 8,
	RunningNoPhysics = 10,
	StrafingNoPhysics = 11,
	Climbing = 12,
	Seated = 13,
	PlatformStanding = 14,
	Dead = 15,
	Physics = 16,
	None = 18
};

enum NameOcclusion {
	NoOcclusion = 0,
	EnemyOcclusion = 1,
	OccludeAll = 2
};

enum HumanoidRigType {
	R15 = 0,
	CustomHumanoid = 1,
	Custom = 2,
	NoneL = 3 // named NoneL if u dont like it fuck yourself
};
