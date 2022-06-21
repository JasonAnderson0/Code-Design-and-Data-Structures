#pragma once
#include "raylib.h"
#include <vector>
#include "Hashtable.h"
#include <string>


class ResourceManager
{
public:

	~ResourceManager();


	Texture2D loadTexture(const char* path);
private:
	bool textureLoaded = false;
	Hashtable<std::string, Texture2D> m_textures;

}; 