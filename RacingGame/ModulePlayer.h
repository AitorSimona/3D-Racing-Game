#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f/5.0f
#define TURN_DEGREES 10.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	vec3 position = { 0.0f,0.0f,0.0f };

	PhysVehicle3D* vehicle = nullptr;
	float turn = 0.0f;
	float acceleration = 0.0f;
	float brake = 0.0f;
};