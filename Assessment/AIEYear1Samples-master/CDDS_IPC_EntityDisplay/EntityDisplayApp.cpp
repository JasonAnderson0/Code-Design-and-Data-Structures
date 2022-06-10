#include "EntityDisplayApp.h"
#include <windows.h>

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {

}

EntityDisplayApp::~EntityDisplayApp() 
{

}


bool EntityDisplayApp::Startup() {

	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);
	fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MySharedMemory");
	intFileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MySharedInt");

	return true;
}

void EntityDisplayApp::Shutdown() {
	//UnmapViewOfFile(data);
	CloseHandle(fileHandle);
	CloseWindow();        // Close window and OpenGL context
}

void EntityDisplayApp::Update(float deltaTime) 
{
	int* intdata = (int*)MapViewOfFile(intFileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int));

	Entity* data = (Entity*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(m_entities));

	m_entities.resize(*intdata);

	for (int i = 0; i < *intdata; i++)
	{
		m_entities[i] = data[i];
	}




	UnmapViewOfFile(data);
	UnmapViewOfFile(intdata);
}

void EntityDisplayApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// draw entities
	for (auto& entity : m_entities) {
		DrawRectanglePro(
			Rectangle{ entity.x, entity.y, entity.size, entity.size }, // rectangle
			Vector2{ entity.size / 2, entity.size / 2 }, // origin
			entity.rotation,
			Color{ entity.r, entity.g, entity.b, 255 });
	}

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}