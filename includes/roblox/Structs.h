#pragma once

#include <variant>
#include <string>

struct Vector3 {
	float x, y, z;
};

struct Vector2 {
	float x, y;
};

struct Color3 {
	float r, g, b;
};

// Humanoid

enum class HumanoidStateType { // with roblox enum classs that are important in memory define the number they are assigned to
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

enum class NameOcclusion {
	NoOcclusion = 0,
	EnemyOcclusion = 1,
	OccludeAll = 2
};

enum class HumanoidRigType {
	R15 = 0,
	CustomHumanoid = 1,
	Custom = 2,
	None = 3
};

enum class HealthDisplayType {
	DisplayWhenDamaged = 0,
	AlwaysOn = 1,
	AlwaysOff =2
};

enum class Axis { // dont matter defining
	X,
	Y,
	Z
};

enum class Material {
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

enum class DisplayDistanceType {
	Viewer = 0,
	Subject = 1,
	None = 2
};

// basepart

enum class PartType {
	Ball = 0,
	Block = 1,
	Cylinder = 2,
	Wedge = 3,
	CornerWedge = 4
};

struct UDim {
    float scale_x;
    int offset_x;
};

struct UDim2 {
    float scale_x;
    int offset_x;
    float scale_y;
    int offset_;
};

struct Matrix3 {
    float elt[ 3 ][ 3 ];
};

struct CFrame {
    Matrix3 rotation;
    Vector3 translation;
};

struct NumberRange {
    float min, max;
};

struct Rect {
    float X0, Y0, X1, Y1;
};

// just store the ptr, if the mf wants to fuck with a god damn color sequence attributes he can do it his fucking self
struct ColorSequence { uintptr_t ptr; };
struct NumberSequence { uintptr_t ptr; };
struct Font { uintptr_t ptr; };

// Instance attributes
using AttributeValue = std::variant<
    std::string,
    bool,
    double,
    UDim,
    UDim2,
    int32_t, // brick color
    Color3,
    Vector2,
    Vector3,
    CFrame,
    ColorSequence, // Color Sequence TODO IMPLEMENT
    NumberSequence, // number sequence TODO IMPLEMENT
    Font, // font TODO IMPLEMENT
    NumberRange,
    Rect
>;

struct Attribute {
    std::string attribute_name;
    AttributeValue attribute_value;
};

inline uintptr_t ShutUpFuckingWarning = 0; // death to clangd