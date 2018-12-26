#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	// --- Map stuff ---
	Cube CreateCube(vec3 size = { 1.0f,1.0f,1.0f }, vec3 pos = { 0.0f, 0.0f, 0.0f }, Color color = White, float angle = 0.0f, vec3 u = (0.0f, 0.0f, 0.0f), float mass = 0.0f, bool draw = true, bool collider = true);
	Cylinder CreateCylinder(float radius = 1.0f, float height = 1.0f, vec3 pos = { 0.0f,0.0f,0.0f }, Color color = White, bool flip = true, float angle = 0.0f, vec3 u = { 0.0f, 0.0f, 0.0f }, float mass = 0.0f, bool draw = true, bool collider = true);

	void UpdateTime(float dt);

	// --- Sensor stuff ---
	void CreateEndLine(vec3 size = { 1.0f,1.0f,1.0f }, vec3 pos = { 0.0f, 0.0f, 0.0f });



public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/
	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	// --- Lists of primitives ---
	p2List<Cube> cubes;
	p2List<Cylinder> cylinders;

	// --- Map parameters ---
	vec3 orthonormal_x = { 0.0f,0.0f,0.0f }, orthonormal_y = { 0.0f,0.0f,0.0f }, orthonormal_z = { 0.0f,0.0f,0.0f }, vec3_zero = { 0.0f,0.0f,0.0f };
	float RWIDTH = 12.0f, RHEIGHT = 0.5f, RLENGTH = 30.0f;
	float GW = 150.0f, GH = 15.0f, GL = 100.0f;
	float TUWIDTH = 6.0f, TUHEIGHT = 45.0f, TULENGTH = 144.0f;

	// --- End Line parameters ---
	float EndLine_Width = 1.0f, EndLine_Length = 1.0f, Bar_Radius = 0.2f, Bar_Height = 30.0f;
	PhysBody3D* Endlap_sensor = nullptr;
	Cube sensor;


	// --- Hinge stuff ---
	PhysBody3D* bodyA = nullptr;
	PhysBody3D* bodyA2 = nullptr;
	PhysBody3D* bodyA3 = nullptr;
	PhysBody3D* bodyA4 = nullptr;
	Cube Rot_cube;
	Cube Rot_cube2;
	Cube Rot_cube3;
	Cube Rot_cube4;
	float HingecylinderRW = 6.0f, HingecylinderRealW = 1.5f, HingecylinderRH = 25.0f, HingecubeW = 6.0f, HingecubeH = 1.0f, HingecubeL = 42.0f;

	mat4x4 transform;

	// --- Gameplay stuff ---

	uint laps = 0;
	int minutes = 1;
	float seconds = 30;
	int max_minutes = 1;
	float max_seconds = 30;
	bool timeup = false;
	bool victory = false;
	uint max_laps = 2;
	bool game_end = false;

	// --- FX ---
	uint engine_fx = 0;
	uint jump_fx = 0;
	uint crash_fx = 0;
	uint brake_fx = 0;
	uint game_over_fx = 0;
};
