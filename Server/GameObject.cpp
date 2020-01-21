#include "GameObject.h"

GameObject* LinkingContext::GetGameObject(uint32_t inNetwork)
{

	auto it = mNetworkIdToGameObjectMap.find(inNetwork);
	if (it != mNetworkIdToGameObjectMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

uint32_t LinkingContext::GetNetworkId(GameObject* inGameObject,bool needCreate)
{

	auto it = mGameObjectToNetworkIdMap.find(inGameObject);
	if (it != mGameObjectToNetworkIdMap.end())
	{
		return it->second;
	}
	else if(needCreate)
	{
		uint32_t network_id = mNextworkId;
		AddGameObject(inGameObject, network_id);
		return network_id;
	}
	else
	{
		return 0;
	}
}


void LinkingContext::AddGameObject(GameObject* inGameObject, uint32_t inNetworkId)
{
	mGameObjectToNetworkIdMap[inGameObject] = inNetworkId;
	mNetworkIdToGameObjectMap[inNetworkId] = inGameObject;
}

void LinkingContext::RemoveObject(GameObject* inGameObject)
{
	uint32_t network_id = mGameObjectToNetworkIdMap[inGameObject];
	mGameObjectToNetworkIdMap.erase(inGameObject);
	mNetworkIdToGameObjectMap.erase(network_id);
}


