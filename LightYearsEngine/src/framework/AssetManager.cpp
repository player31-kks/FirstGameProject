#include "framework/AssetManager.h"



namespace ly{

	AssetManager::AssetManager() {};


	AssetManager& ly::AssetManager::Get()
	{
		if (!assetManager) {
			assetManager = unique<AssetManager>(new AssetManager);
		}
		return *assetManager;
	}


	unique<AssetManager> AssetManager::assetManager{ nullptr };



	shared<sf::Texture> ly::AssetManager::LoadTexture(const std::string& path)
	{
		auto found = mLoadedTextureMap.find(path);
		if (found != mLoadedTextureMap.end()) {
			return found->second;
		}

		shared<sf::Texture> newTexture = std::make_shared<sf::Texture>();
		if (newTexture->loadFromFile(path)) {
			mLoadedTextureMap.insert({ path,newTexture });
			return newTexture;
		}

		return shared<sf::Texture> {nullptr};
	}

	void AssetManager::ClearCycle()
	{
		for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();) 
		{
			if (iter->second.use_count()==1) {
				LOG("cleaning texture : %s",iter->first.c_str());
				iter = mLoadedTextureMap.erase(iter);
			}
			else {
				++iter;
			}
		}
	}
}
