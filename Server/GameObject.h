#pragma once

#include <cstdio>
#include <stdint.h>
#include <unordered_map>


class GameObject
{
	
};


class LinkingContext
{
public:
	uint32_t GetNetworkId(GameObject* inGameObject, bool needCreate);
	

	GameObject* GetGameObject(uint32_t inNetwork);
	

	void AddGameObject(GameObject* inGameObject, uint32_t inNetworkId);
	void RemoveObject(GameObject* inGameObject);

private:
	std::unordered_map<uint32_t, GameObject*>
		mNetworkIdToGameObjectMap;
	std::unordered_map<GameObject*, uint32_t>
		mGameObjectToNetworkIdMap;

	uint32_t mNextworkId;
};

