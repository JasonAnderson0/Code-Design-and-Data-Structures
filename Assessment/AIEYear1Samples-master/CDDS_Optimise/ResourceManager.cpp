#include "ResourceManager.h"


ResourceManager::~ResourceManager()
{
}



Texture2D ResourceManager::loadTexture(const char* path)
{
	//std::string key(path);
	//auto iter = m_textures.find(key);
	//if(iter != m_textures.end()){
	// //already loaded texture
	// return iter->second;
	//  }
	//else{
	// //load and store in hashtable
	//Texture2D tex = LoadTexture(path);
	//m_textures[key] = tex;
	//return tex;
	//}

	//check if its been loaded before

	if (textureLoaded == false) {
		Texture2D tex = LoadTexture(path);
		textureLoaded = true;
		return tex;
	}
	else {
		return m_textures[path];
	}	
}

