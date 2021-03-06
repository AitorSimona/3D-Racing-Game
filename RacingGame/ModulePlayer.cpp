#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1, 4);
	car.chassis_offset.Set(0, 1, 0);
	car.mass = 200.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.8f;
	car.maxSuspensionTravelCm = 750.0f;
	car.frictionSlip = 200.0f;
	car.maxSuspensionForce = 3000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.0f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.0f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 12, 10);
	
	engine_timer.Start();
	brake_timer.Start();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	auxpos = vehicle->GetPosition();

	// --- JUMP ---
	if (jump_cap) 
	{
		jump_timer += 1.0f * dt;

		if (jump_timer >= jump_lapse) 
		{
			jump_cap = false;
			jump_timer = 0.0f;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		if (engine_timer.Read() > 7.0f*1000.0f && App->scene_intro->laps != App->scene_intro->max_laps && !App->scene_intro->game_end)
		{
			App->audio->PlayFx(App->scene_intro->engine_fx, 1);
			engine_timer.Start();
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && App->scene_intro->laps != App->scene_intro->max_laps && !App->scene_intro->game_end)
	{
		acceleration = MAX_ACCELERATION;
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && App->scene_intro->laps != App->scene_intro->max_laps && !App->scene_intro->game_end)
	{
		if (vehicle->GetKmh() > 0.0f)
		{
			brake = BRAKE_POWER / 25;

			if (brake_timer.Read() > 5.0f*1000.0f)
			{
					App->audio->PlayFx(App->scene_intro->brake_fx);
					brake_timer.Start();
			}
		}
		else
		acceleration = -MAX_ACCELERATION;

	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() < 0)
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES*1.5f;
		}
		else
		{
			if (turn < TURN_DEGREES)
				turn += TURN_DEGREES;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() < 0)
		{
			if (turn < TURN_DEGREES)
				turn -= TURN_DEGREES * 1.5f;
		}
		else
		{
			if (turn > -TURN_DEGREES)
				turn -= TURN_DEGREES;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && !jump_cap && !App->scene_intro->game_end)
	{
		vehicle->Push(0.0f, jump_force, 0.0f);
		jump_cap = true;
		App->audio->PlayFx(App->scene_intro->jump_fx);
	}

	if (vehicle->GetKmh() > 80)
		acceleration = 0.0f;

	// --- RESPAWN ---

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN
		|| App->scene_intro->victory
		|| App->scene_intro->timeup
		|| auxpos.y < -50.0f)
	{
		App->scene_intro->timeup = false;
		App->scene_intro->victory = false;
		App->scene_intro->minutes = App->scene_intro->max_minutes;
		App->scene_intro->seconds = App->scene_intro->max_seconds;

		vehicle->SetLinV(App->scene_intro->vec3_zero, *vehicle);
		vehicle->SetAngV(App->scene_intro->vec3_zero, *vehicle);

		vehicle->SetTransform(IdentityMatrix.M);
		jump_cap = false;
		jump_timer = 0.0f;

		if (App->scene_intro->game_end)
		{
			App->scene_intro->game_end = false;
			App->scene_intro->timeupcount = 0;
		}

		if (App->scene_intro->laps == App->scene_intro->max_laps)
		{
			App->scene_intro->laps = 0;
			App->audio->PlayMusic("audio/Main_Track.ogg", 0.0f);
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();	

	App->camera->LookAt(vehicle->GetPosition());
	App->camera->Position = (vehicle->GetPosition() - vehicle->GetForwardvec3() * 10) + vec3(0, 3, 0);

	char title[150];
	if(App->scene_intro->laps != App->scene_intro->max_laps && !App->scene_intro->game_end)
	sprintf_s(title, "%.1f Km/h || Time: %i:%.1f || laps: %i  ", vehicle->GetKmh(), App->scene_intro->minutes,App->scene_intro->seconds, App->scene_intro->laps);
	else if (App->scene_intro->maxtimeups == App->scene_intro->timeupcount)
	sprintf_s(title, "%.1f Km/h || Time: %i:%.1f || laps: %i  MAX TIMEUPS REACHED - YOU LOSE!!!  PRESS --- R --- TO PLAY AGAIN", vehicle->GetKmh(), App->scene_intro->minutes, App->scene_intro->seconds, App->scene_intro->laps);
	else
	sprintf_s(title, "%.1f Km/h || Time: %i:%.1f || laps: %i CONGRATULATIONS - YOU WIN!!! PRESS --- R --- TO PLAY AGAIN", vehicle->GetKmh(), App->scene_intro->minutes, App->scene_intro->seconds, App->scene_intro->laps);
	
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



