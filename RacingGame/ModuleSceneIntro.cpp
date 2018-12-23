#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));

	// Map parameters, orientation
	orthonormal_x = { 1.0f, 0.0f, 0.0f };
	orthonormal_y = { 0.0f, 1.0f, 0.0f };
	orthonormal_z = { 0.0f, 0.0f, 1.0f };


	// --- Main Road ---
	// --- 1st part ---
	Cube cu = CreateCube(vec3(RWIDTH, RHEIGHT, RLENGTH), vec3_zero);
	Cube cu2 = CreateCube(vec3(RWIDTH, RHEIGHT, RLENGTH), vec3(cu.GetPos().x, cu.GetPos().y, cu.GetPos().z + cu.GetSize().z / 2.0f + RLENGTH / 2.0f));
	Cylinder cy = CreateCylinder(RWIDTH / 2.0f, RHEIGHT, vec3(cu.GetPos().x, cu2.GetPos().y, cu2.GetPos().z + cu2.GetSize().z / 2.0f));
	Cube cu6 = CreateCube(vec3(RWIDTH, RHEIGHT, 6.0f * RLENGTH), vec3(cy.GetPos().x, cy.GetPos().y, cy.GetPos().z + (6.0f * RLENGTH) / 2.0f));
	Cube cu7 = CreateCube(vec3(RWIDTH, RHEIGHT, RLENGTH / 2.0f), vec3(cu6.GetPos().x, cu6.GetPos().y, cu6.GetPos().z + cu6.GetSize().z / 2.0f), White, -20.0f, orthonormal_x);

	// --- 2nd part ---
	Cube cu8 = CreateCube(vec3(3.0f * RWIDTH, RHEIGHT, 5.0f * RLENGTH), vec3(cu7.GetPos().x, cu7.GetPos().y + cu7.GetSize().y / 2.0f + RHEIGHT / 2.0f, cu7.GetPos().z *1.25f - cu7.GetSize().z * 0.1f + (3.0f * RLENGTH) / 2.0f));
	Cylinder cy5 = CreateCylinder((3.0f * RWIDTH) / 2.0f, RHEIGHT, vec3(cu8.GetPos().x, cu8.GetPos().y, cu8.GetPos().z + cu8.GetSize().z / 2.0f));
	Cube cu9 = CreateCube(vec3(4.0f * RLENGTH, RHEIGHT, 3.0f * RWIDTH), vec3(cy5.GetPos().x + (4.0f * RLENGTH) / 2.0f, cy5.GetPos().y, cy5.GetPos().z));
	Cylinder cy6 = CreateCylinder((3.0f * RWIDTH) / 2.0f, RHEIGHT, vec3(cu9.GetPos().x + cu9.GetPos().x / 2.0f, cu9.GetPos().y, cu9.GetPos().z));
	Cube cu10 = CreateCube(vec3(2.0f * RLENGTH, RHEIGHT,  RWIDTH), vec3(cy6.GetPos().x + RLENGTH, cy6.GetPos().y + RHEIGHT * 3.0f, cy6.GetPos().z), White, 20.0f, orthonormal_z);
	Cube cu11 = CreateCube(vec3(2.0f * RLENGTH, RHEIGHT, 3.0f * RWIDTH), vec3(cu10.GetPos().x + cu10.GetSize().x + RLENGTH/ 2.0f - 4.0f, cu10.GetPos().y + cu10.GetSize().z * tan(DEGTORAD * 30.0f) - 0.4f, cu10.GetPos().z), White);
	Cylinder cy7 = CreateCylinder(RWIDTH / 2.0f, 50.0f * RHEIGHT, vec3(cu11.GetPos().x + cu11.GetSize().x / 3.0f - (RWIDTH / 2.0f), cu11.GetPos().y + cu11.GetSize().y / 2.0f - (50.0f * RHEIGHT) / 2.0f, cu11.GetPos().z), White);
	Cube cu12 = CreateCube(vec3(3.0f * RWIDTH, RHEIGHT, 2.0f * RLENGTH), vec3(cu11.GetPos().x + cu11.GetSize().x / 2.0f - (3.0f * RWIDTH) / 2.0f, cy6.GetPos().y, cu11.GetPos().z - (3.0f *RLENGTH) / 2.0f - cu11.GetSize().z / 2.0f + 4.0f), White, -10.0f, orthonormal_x);
	Cube cu14 = CreateCube(vec3(1.0f * RWIDTH, RHEIGHT, 2.0f * RLENGTH), vec3(cu12.GetPos().x, cu12.GetPos().y, cu12.GetPos().z - cu12.GetSize().z / 2.0f / 2.0f), White);
	Cube cu15 = CreateCube(vec3(3.0f * RWIDTH, RHEIGHT, 2.0f * RLENGTH), vec3(cu14.GetPos().x, cu14.GetPos().y, cu14.GetPos().z - 1.2f * cu14.GetSize().z), White);
	Cube cu16 = CreateCube(vec3(3.0f * RWIDTH, RHEIGHT, 2.0f * RLENGTH), vec3(cu15.GetPos().x, cu15.GetPos().y, cu15.GetPos().z - 1.2f * cu15.GetSize().z), White);


	// --- 3rd part ---
	Cylinder cy8 = CreateCylinder((3.0f * RWIDTH) / 2.0f, RHEIGHT, vec3(cu16.GetPos().x, cu16.GetPos().y, cu16.GetPos().z - cu16.GetSize().z / 2.0f));
	Cube cu17 = CreateCube(vec3(2.0f * RLENGTH, RHEIGHT, 3.0f * RWIDTH), vec3(cy8.GetPos().x + (2.0f * RLENGTH) / 2.0f, cy8.GetPos().y, cy8.GetPos().z));
	Cylinder cy9 = CreateCylinder((3.0f * RWIDTH) / 2.0f, RHEIGHT, vec3(cu17.GetPos().x + cu17.GetSize().x / 2.0f, cu17.GetPos().y, cu17.GetPos().z));
	Cube cu18 = CreateCube(vec3(3.0f * RWIDTH, RHEIGHT, 6.0f * RLENGTH), vec3(cy9.GetPos().x, cy9.GetPos().y, cy9.GetPos().z - (6.0f * RLENGTH) / 2.0f));
	Cylinder cy10 = CreateCylinder((3.0f * RWIDTH) / 2.0f, RHEIGHT, vec3(cu18.GetPos().x, cu18.GetPos().y, cu18.GetPos().z - cu18.GetSize().z / 2.0f));
	Cube cu19 = CreateCube(vec3(4.0f * RLENGTH, RHEIGHT, 3.0f * RWIDTH), vec3(cy10.GetPos().x + (4.0f * RLENGTH) / 2.0f, cy10.GetPos().y, cy10.GetPos().z));
	Cylinder cy11 = CreateCylinder((3.0f * RWIDTH) / 2.0f, RHEIGHT, vec3(cu19.GetPos().x + cu19.GetSize().x / 2.0f, cu19.GetPos().y, cu19.GetPos().z));
	Cube cu20 = CreateCube(vec3(3.0f * RWIDTH, RHEIGHT, 3.0f * RLENGTH), vec3(cy11.GetPos().x, cy11.GetPos().y, cy11.GetPos().z + (3.0f * RLENGTH) / 2.0f));
	Cylinder cy12 = CreateCylinder((3.0f * RWIDTH) / 2.0f, RHEIGHT, vec3(cu20.GetPos().x, cu20.GetPos().y, cu20.GetPos().z + cu20.GetSize().z / 2.0f));
	Cube cu21 = CreateCube(vec3(RLENGTH, RHEIGHT, 3.0f * RWIDTH), vec3(cy12.GetPos().x - RLENGTH / 2.0f, cy12.GetPos().y, cy12.GetPos().z));
	Cube cu22 = CreateCube(vec3(3.0f * RLENGTH, RHEIGHT, 3.0f * RWIDTH), vec3(cu21.GetPos().x - cu21.GetSize().x, cu21.GetPos().y + cu21.GetSize().y, cu21.GetPos().z ), White, -30.0f, orthonormal_z);

	// --- Tunnel ---
	Cube tunnel_wall = CreateCube(vec3(TUWIDTH, TUHEIGHT, TULENGTH), vec3(cu17.GetPos().x + (2.0f * RLENGTH) / 2.0f - cy9.radius - TUWIDTH / 2.0f, cu17.GetPos().y, cy9.GetPos().z - cy9.radius - TULENGTH / 2.0f), White);
	Cube tunnel_wall2 = CreateCube(vec3(TUWIDTH, TUHEIGHT, TULENGTH), vec3(cu17.GetPos().x + (2.0f * RLENGTH) / 2.0f + cy9.radius + TUWIDTH / 2.0f, cu17.GetPos().y, cy9.GetPos().z - cy9.radius - TULENGTH / 2.0f), White);
	Cube tunnel_wall3 = CreateCube(vec3((tunnel_wall2.GetPos().x + tunnel_wall2.GetSize().x / 2.0f) - (tunnel_wall.GetPos().x - tunnel_wall.GetSize().x / 2.0f), TUWIDTH / 4.0f, TULENGTH), vec3(tunnel_wall.GetPos().x + tunnel_wall.GetSize().x / 2.0f + cu18.GetSize().x / 2.0f, tunnel_wall.GetPos().y + tunnel_wall.GetSize().y / 2.0f + (TUWIDTH / 4.0f) / 2.0f, tunnel_wall.GetPos().z), White);
	//_tunnel

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();

	// Blit cubes
	p2List_item<Cube>* cube_item = cubes.getFirst();

	while (cube_item != nullptr) {
		cube_item->data.Render();

		cube_item = cube_item->next;
	}

	// Blit cylinders
	p2List_item<Cylinder>* cylinder_item = cylinders.getFirst();

	while (cylinder_item != nullptr) {
		cylinder_item->data.Render();

		cylinder_item = cylinder_item->next;
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

// Generic functions
Cube ModuleSceneIntro::CreateCube(vec3 size, vec3 pos, Color color, float angle, vec3 u, float mass, bool draw, bool collider)
{
	Cube tmpcube(size.x, size.y, size.z);
	tmpcube.SetPos(pos.x, pos.y, pos.z);
	tmpcube.color = color;

	if (angle != 0)
		tmpcube.SetRotation(angle, vec3(u.x, u.y, u.z));
	if (collider)
		App->physics->AddBody(tmpcube, mass);
	if (draw)
		cubes.add(tmpcube);

	return tmpcube;
}

Cylinder ModuleSceneIntro::CreateCylinder(float radius, float height, vec3 pos, Color color, bool flip, float angle, vec3 u, float mass, bool draw, bool collider)
{
	Cylinder cy(radius, height);
	cy.SetPos(pos.x, pos.y, pos.z);
	cy.color = color;

	if (flip)
		cy.SetRotation(90.0f, vec3(0.0f, 0.0f, 1.0f));

	if (angle != 0.0f)
		cy.SetRotation(angle, vec3(u.x, u.y, u.z));

	if (collider)
		App->physics->AddBody(cy, mass);

	if (draw)
		cylinders.add(cy);

	return cy;
}

