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

	Cube CreateCube(vec3 size = { 1.0f,1.0f,1.0f }, vec3 pos = { 0.0f, 0.0f, 0.0f }, Color color = White, float angle = 0.0f, vec3 u = (0.0f, 0.0f, 0.0f), float mass = 0.0f, bool draw = true, bool collider = true);
	Cylinder CreateCylinder(float radius = 1.0f, float height = 1.0f, vec3 pos = { 0.0f,0.0f,0.0f }, Color color = White, bool flip = true, float angle = 0.0f, vec3 u = { 0.0f, 0.0f, 0.0f }, float mass = 0.0f, bool draw = true, bool collider = true);

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

	// Lists of primitives
	p2List<Cube> cubes;
	p2List<Cylinder> cylinders;

	// Map parameters
	vec3 orthonormal_x = { 0.0f,0.0f,0.0f }, orthonormal_y = { 0.0f,0.0f,0.0f }, orthonormal_z = { 0.0f,0.0f,0.0f }, vec3_zero = { 0.0f,0.0f,0.0f };
	float RWIDTH = 12.0f, RHEIGHT = 0.5f, RLENGTH = 30.0f;
	float GW = 150.0f, GH = 15.0f, GL = 100.0f;
	float TUWIDTH = 6.0f, TUHEIGHT = 45.0f, TULENGTH = 144.0f;

};
