#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

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

	// Hinges Default Values 
	HingecylinderRW = RWIDTH / 2.0f; 
	HingecylinderRealW = RWIDTH / 8.0f;
	HingecylinderRH = 50.0f * RHEIGHT; 

	HingecubeW = RWIDTH / 2.0f; 
	HingecubeH = 2.0f * RHEIGHT; 
	HingecubeL = RLENGTH + RWIDTH; 

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

	// --- Tunnel (end) ---
	Cube tunnel_wall = CreateCube(vec3(TUWIDTH, TUHEIGHT, TULENGTH), vec3(cu17.GetPos().x + (2.0f * RLENGTH) / 2.0f - cy9.radius - TUWIDTH / 2.0f, cu17.GetPos().y, cy9.GetPos().z - cy9.radius - TULENGTH / 2.0f), White);
	Cube tunnel_wall2 = CreateCube(vec3(TUWIDTH, TUHEIGHT, TULENGTH), vec3(cu17.GetPos().x + (2.0f * RLENGTH) / 2.0f + cy9.radius + TUWIDTH / 2.0f, cu17.GetPos().y, cy9.GetPos().z - cy9.radius - TULENGTH / 2.0f), White);
	Cube tunnel_wall3 = CreateCube(vec3((tunnel_wall2.GetPos().x + tunnel_wall2.GetSize().x / 2.0f) - (tunnel_wall.GetPos().x - tunnel_wall.GetSize().x / 2.0f), TUWIDTH / 4.0f, TULENGTH), vec3(tunnel_wall.GetPos().x + tunnel_wall.GetSize().x / 2.0f + cu18.GetSize().x / 2.0f, tunnel_wall.GetPos().y + tunnel_wall.GetSize().y / 2.0f + (TUWIDTH / 4.0f) / 2.0f, tunnel_wall.GetPos().z), White);

	//tunnel

	// --- Hinges ---

	// --- straight road ---
	Rot_cube = CreateCube(vec3(HingecubeW, HingecubeH, HingecubeL), vec3(cu6.GetPos().x + 20.0f, cu6.GetPos().y + 2.0f * HingecubeH, cu6.GetPos().z - HingecubeL / 2.0f), Red, 0.0f, vec3(0.0f, 0.0f, 0.0f), 0.0f, false, false);
	bodyA = App->physics->AddBody(Rot_cube, 10000.0f);
	Cylinder Rot_cylinder = CreateCylinder(HingecylinderRW, HingecylinderRH, vec3(Rot_cube.GetPos().x, Rot_cube.GetPos().y - HingecylinderRH / 2.0f, Rot_cube.GetPos().z), Red, true, 0.0f, vec3_zero, 0.0f, false, false);
	PhysBody3D* bodyB = App->physics->AddBody(Rot_cylinder, 10000.0f);
	Cylinder Real_cylinder = CreateCylinder(HingecylinderRealW, HingecylinderRH, vec3(Rot_cube.GetPos().x, Rot_cube.GetPos().y - HingecylinderRH / 2.0f, Rot_cube.GetPos().z), Red);

	Rot_cube2 = CreateCube(vec3(HingecubeW, HingecubeH, HingecubeL), vec3(cu6.GetPos().x - 20.0f, cu6.GetPos().y + 2.0f * HingecubeH, cu6.GetPos().z + HingecubeL / 2.0f), Red, 0.0f, vec3_zero, 0.0f, false, false);
	bodyA2 = App->physics->AddBody(Rot_cube2, 10000.0f);
	Cylinder Rot_cylinder2 = CreateCylinder(HingecylinderRW, HingecylinderRH, vec3(Rot_cube2.GetPos().x, Rot_cube2.GetPos().y - HingecylinderRH / 2.0f, Rot_cube2.GetPos().z), Red, true, 0.0f, vec3_zero, 0.0f, false, false);
	PhysBody3D* bodyB2 = App->physics->AddBody(Rot_cylinder2, 10000.0f);
	Cylinder Real_cylinder2 = CreateCylinder(HingecylinderRealW, HingecylinderRH, vec3(Rot_cube2.GetPos().x, Rot_cube2.GetPos().y - HingecylinderRH / 2.0f, Rot_cube2.GetPos().z), Red);

	bodyA->GetBody()->setLinearFactor(btVector3(0, 0, 0));
	bodyA2->GetBody()->setLinearFactor(btVector3(0, 0, 0));
	bodyB->GetBody()->setAngularFactor(btVector3(0, 0, 0));
	bodyB2->GetBody()->setAngularFactor(btVector3(0, 0, 0));

	App->physics->AddConstraintHinge(*bodyA, *bodyB, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), true, true);
	App->physics->AddConstraintHinge(*bodyA2, *bodyB2, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), true, true);
	
	//straight road

	// --- Separated platforms ---
	Rot_cube3 = CreateCube(vec3(HingecubeW, HingecubeH, HingecubeL), vec3(cu15.GetPos().x + 20.0f, cu15.GetPos().y + 2.0f * HingecubeH, cu15.GetPos().z - HingecubeL / 2.0f), Red, 0.0f, vec3(0.0f, 0.0f, 0.0f), 0.0f, false, false);
	bodyA3 = App->physics->AddBody(Rot_cube3, 10000.0f);
	Cylinder Rot_cylinder3 = CreateCylinder(HingecylinderRW, HingecylinderRH, vec3(Rot_cube3.GetPos().x, Rot_cube3.GetPos().y - HingecylinderRH / 2.0f, Rot_cube3.GetPos().z), Red, true, 0.0f, vec3_zero, 0.0f, false, false);
	PhysBody3D* bodyB3 = App->physics->AddBody(Rot_cylinder3, 10000.0f);
	Cylinder Real_cylinder3 = CreateCylinder(HingecylinderRealW, HingecylinderRH, vec3(Rot_cube3.GetPos().x, Rot_cube3.GetPos().y - HingecylinderRH / 2.0f, Rot_cube3.GetPos().z), Red);

	Rot_cube4 = CreateCube(vec3(HingecubeW, HingecubeH, HingecubeL), vec3(cu15.GetPos().x - 20.0f, cu15.GetPos().y + 2.0f * HingecubeH, cu15.GetPos().z + HingecubeL / 2.0f), Red, 0.0f, vec3_zero, 0.0f, false, false);
	bodyA4 = App->physics->AddBody(Rot_cube4, 10000.0f);
	Cylinder Rot_cylinder4 = CreateCylinder(HingecylinderRW, HingecylinderRH, vec3(Rot_cube4.GetPos().x, Rot_cube4.GetPos().y - HingecylinderRH / 2.0f, Rot_cube4.GetPos().z), Red, true, 0.0f, vec3_zero, 0.0f, false, false);
	PhysBody3D* bodyB4 = App->physics->AddBody(Rot_cylinder4, 10000.0f);
	Cylinder Real_cylinder4 = CreateCylinder(HingecylinderRealW, HingecylinderRH, vec3(Rot_cube4.GetPos().x, Rot_cube4.GetPos().y - HingecylinderRH / 2.0f, Rot_cube4.GetPos().z), Red);

	bodyA3->GetBody()->setLinearFactor(btVector3(0, 0, 0));
	bodyA4->GetBody()->setLinearFactor(btVector3(0, 0, 0));
	bodyB3->GetBody()->setAngularFactor(btVector3(0, 0, 0));
	bodyB4->GetBody()->setAngularFactor(btVector3(0, 0, 0));

	App->physics->AddConstraintHinge(*bodyA3, *bodyB3, vec3_zero, vec3_zero, vec3(0.0f, -1.0f, 0.0f), vec3_zero, true, true);
	App->physics->AddConstraintHinge(*bodyA4, *bodyB4, vec3_zero, vec3_zero, vec3(0.0f, 1.0f, 0.0f), vec3_zero, true, true);
	
	//Separated platforms

	// Hinges

	// --- End line ---
	CreateEndLine(vec3(EndLine_Width*3.0f, RHEIGHT * 2.0f, EndLine_Length*1.5f), vec3(cu20.GetPos().x - EndLine_Width*16.5f,cu20.GetPos().y + 1.0f, cu20.GetPos().z));

	Endlap_sensor = App->physics->AddBody(sensor, 0.0f);
	Endlap_sensor->SetAsSensor(true);
	Endlap_sensor->collision_listeners.add(this);

	Cylinder bar = CreateCylinder(Bar_Radius, Bar_Height, vec3(cu20.GetPos().x - cu20.GetSize().x, cu20.GetPos().y - cu20.GetSize().y, cu20.GetPos().z), Green);
	Cylinder bar2 = CreateCylinder(Bar_Radius, Bar_Height, vec3(cu20.GetPos().x + cu20.GetSize().x, cu20.GetPos().y - cu20.GetSize().y, cu20.GetPos().z), Green);
	Cube finish_line = CreateCube(vec3(bar2.GetPos().x - bar.GetPos().x, Bar_Height / 6.0f, RHEIGHT), vec3(cu20.GetPos().x, cu20.GetPos().y - cu20.GetSize().y + Bar_Height / 2.0f, cu20.GetPos().z), Green);
	//End line

	// --- Obstacles ---

	// --- straight road ---
	Cylinder cy13 = CreateCylinder(1.0f,HingecylinderRH/4.0f, vec3(cu.GetPos().x, cu.GetPos().y + HingecylinderRH / 8.0f, cu.GetPos().z + cu.GetSize().z), Red);
	Cube auxcu = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu.GetPos().x, cu.GetPos().y + HingecylinderRH / 8.0f, cu.GetPos().z + cu.GetSize().z), Green);

	Cylinder cy14 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(cu2.GetPos().x - 3.0f, cu2.GetPos().y + HingecylinderRH / 8.0f, cu2.GetPos().z + cu2.GetSize().z), Red);
	Cube auxcu2 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu2.GetPos().x - 3.0f, cu2.GetPos().y + HingecylinderRH / 8.0f, cu2.GetPos().z + cu2.GetSize().z), Green);

	Cylinder cy15 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(cu6.GetPos().x - 3.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z), Red);
	Cube auxcu3 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu6.GetPos().x - 3.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z), Green);

	Cylinder cy16 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(cu6.GetPos().x + 15.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 20.0f), Red);
	Cube auxcu4 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu6.GetPos().x + 15.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 20.0f), Green);

	Cylinder cy17 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(cu6.GetPos().x + 8.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z), Red);
	Cube auxcu5 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu6.GetPos().x + 8.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z), Green);

	Cylinder cy18 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(cu6.GetPos().x + 15.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 70.0f), Red);
	Cube auxcu6 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu6.GetPos().x + 15.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 70.0f), Green);

	Cylinder cy19 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(cu6.GetPos().x + 4.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 20.0f), Red);
	Cube auxcu7 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu6.GetPos().x + 4.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 20.0f), Green);

	Cylinder cy20 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(cu6.GetPos().x - 4.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 20.0f), Red);
	Cube auxcu8 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(cu6.GetPos().x - 4.0f, cu6.GetPos().y + HingecylinderRH / 8.0f, cu6.GetPos().z + cu6.GetSize().z + 20.0f), Green);
	
	//straight road

	// --- Tunnel obstacles ---

	Cylinder cy21 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x -10.0f , tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 3.0f ), Red);
	Cube auxcu9 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 10.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 3.0f), Green);

	Cylinder cy22 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x - 30.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 3.0f ), Red);
	Cube auxcu10 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 30.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 3.0f), Green);

	Cylinder cy23 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x - 15.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 5.0f), Red);
	Cube auxcu11 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 15.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 5.0f), Green);

	Cylinder cy24 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x - 22.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 6.0f), Red);
	Cube auxcu12 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 22.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 6.0f), Green);


	Cylinder cy25 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x - 10.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 8.0f - 40.0f), Red);
	Cube auxcu13 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 10.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 8.0f - 40.0f), Green);

	Cylinder cy26 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x - 30.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 8.0f - 20.0f), Red);
	Cube auxcu14 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 30.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 8.0f - 20.0f), Green);

	Cylinder cy27 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x - 15.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 10.0f - 40.0f), Red);
	Cube auxcu15 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 15.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 10.0f - 40.0f), Green);

	Cylinder cy28 = CreateCylinder(1.0f, HingecylinderRH / 4.0f, vec3(tunnel_wall2.GetPos().x - 22.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 11.0f - 20.0f), Red);
	Cube auxcu16 = CreateCube(vec3(1.0f, HingecylinderRH / 4.0f, 1.0f), vec3(tunnel_wall2.GetPos().x - 22.0f, tunnel_wall.GetPos().y + HingecylinderRH / 8.0f, tunnel_wall.GetPos().z + tunnel_wall.GetSize().z / 11.0f - 20.0f), Green);


	//Tunnel obstacles

	App->audio->PlayMusic("audio/Main_Track.ogg", 0.0f);

	engine_fx = App->audio->LoadFx("audio/Engine_fx.wav");
	jump_fx = App->audio->LoadFx("audio/jump_fx.wav");
	crash_fx = App->audio->LoadFx("audio/Crash_fx.wav");
	brake_fx = App->audio->LoadFx("audio/brake_fx.wav");
	game_over_fx = App->audio->LoadFx("audio/game_over.wav");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	cubes.clear();
	cylinders.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	//Plane p(0, 1, 0, 0);
	//p.axis = true;
	//p.Render();

	if(laps!=max_laps)
	UpdateTime(dt);

	// --- Win Condition ---
	if (laps == max_laps && !game_end)
	{
		game_end = true;
		App->audio->PlayMusic("audio/Victory_Track.ogg", 0.0f);

		App->player->SetLinV(App->scene_intro->vec3_zero);
		App->player->SetAngV(App->scene_intro->vec3_zero);

		App->player->vehicle->SetTransform(IdentityMatrix.M);
		App->player->jump_cap = false;
		App->player->jump_timer = 0.0f;
	}

	if (game_end)
	{
		App->player->jump_cap = true;
		App->player->jump_timer = 0.0f;
	}

	// Blit cubes
	p2List_item<Cube>* cube_item = cubes.getFirst();

	while (cube_item != nullptr) 
	{
		cube_item->data.Render();

		cube_item = cube_item->next;
	}

	// Blit cylinders
	p2List_item<Cylinder>* cylinder_item = cylinders.getFirst();

	while (cylinder_item != nullptr) 
	{
		cylinder_item->data.Render();

		cylinder_item = cylinder_item->next;
	}

	// Update hinges
	Rot_cube.Render();
	Rot_cube2.Render();
	Rot_cube3.Render();
	Rot_cube4.Render();

	bodyA->GetTransform(transform.M);
	Rot_cube.transform = transform;
	bodyA2->GetTransform(transform.M);
	Rot_cube2.transform = transform;

	bodyA3->GetTransform(transform.M);
	Rot_cube3.transform = transform;
	bodyA4->GetTransform(transform.M);
	Rot_cube4.transform = transform;

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == Endlap_sensor && body2 == (PhysBody3D*)App->player->vehicle) {

		laps++;
		
		App->scene_intro->max_seconds -= 10;

		if(laps!=max_laps)
		victory = true;
	}
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
	Cylinder tmpcylinder(radius, height);
	tmpcylinder.color = color;
	tmpcylinder.SetPos(pos.x, pos.y, pos.z);

	if (flip)
		tmpcylinder.SetRotation(90.0f, vec3(0.0f, 0.0f, 1.0f));
	if (angle != 0.0f)
		tmpcylinder.SetRotation(angle, vec3(u.x, u.y, u.z));
	if (collider)
		App->physics->AddBody(tmpcylinder, mass);
	if (draw)
		cylinders.add(tmpcylinder);

	return tmpcylinder;
}

void ModuleSceneIntro::UpdateTime(float dt)
{
	if (minutes >= 0) 
	{
		seconds -= 1.0f * dt;

		if (seconds <= 0)
		{
			seconds = 60.0f;
			minutes -= 1;
		}
	}
	else
	{
		timeup = true;
		App->audio->PlayFx(game_over_fx);
	}
}

void ModuleSceneIntro::CreateEndLine(vec3 size, vec3 pos)
{
	Color c, c2;

	for (int i = 0; i < 3; ++i) 
	{
		if (i % 2 != 0) 
		{
			c = Black;
			c2 = White;
		}
		else 
		{
			c = White;
			c2 = Black;
		}
		for (int j = 0; j < 6; ++j) 
		{
			CreateCube(size, vec3(pos.x + (j * 2 + 0) * size.x, pos.y, pos.z + i * size.z), c, 0.0f, vec3(0.0f, 0.0f, 0.0f), 0.0f, true, false);
			CreateCube(size, vec3(pos.x + (j * 2 + 1) * size.x, pos.y, pos.z + i * size.z), c2, 0.0f, vec3_zero, 0.0f, true, false);
		}

		Cube tmp;
		tmp.size = { 13 * size.x, 5*size.y, 5*size.z  };
		tmp.SetPos(pos.x + tmp.GetSize().x / 2.25f, pos.y, pos.z);
		tmp.axis = true;
		tmp.wire = true;
		tmp.color = Blue;

		sensor = tmp;
	}
}

