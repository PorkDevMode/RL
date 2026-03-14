#pragma once

#include <cstdint>

struct Vector3 {
	float x, y, z;
};

struct Vector2 {
	float x, y;
};

enum HumanoidStateType { // with roblox enums that are important in memory define the number they are assigned to
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

enum HealthDisplayType {
	DisplayWhenDamaged = 0,
	AlwaysOn = 1,
	AlwaysOff =2
};

enum Axis { // dont matter defining
	X,
	Y,
	Z
};

enum Material {
    Plastic = 256,
    SmoothPlastic = 272,
    Neon = 288,
    Wood = 512,
    WoodPlanks = 528,
    Marble = 784,
    Basalt = 788,
    Slate = 800,
    CrackedLava = 804,
    Concrete = 816,
    Limestone = 820,
    Granite = 832,
    Pavement = 836,
    Brick = 848,
    Pebble = 864,
    Cobblestone = 880,
    Rock = 896,
    Sandstone = 912,
    CorrodedMetal = 1040,
    DiamondPlate = 1056,
    Foil = 1072,
    Metal = 1088,
    Grass = 1280,
    LeafyGrass = 1284,
    Sand = 1296,
    Fabric = 1312,
    Snow = 1328,
    Mud = 1344,
    Ground = 1360,
    Asphalt = 1376,
    Salt = 1392,
    Ice = 1536,
    Glacier = 1552,
    Glass = 1568,
    ForceField = 1584,
    Air = 1792,
    Water = 2048,
    Cardboard = 2304,
    Carpet = 2305,
    CeramicTiles = 2306,
    ClayRoofTiles = 2307,
    RoofShingles = 2308,
    Leather = 2309,
    Plaster = 2310,
    Rubber = 2311
};

inline uintptr_t ShutUpFuckingWarning = 0; // death to clangd