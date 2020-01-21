#include "GameObject.h"

//LinkingContext LinkingContext

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
		uint32_t network_id = mNextworkId++;
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
	mGameObjectToNetworkIdMap[ inGameObject] = inNetworkId;
	mNetworkIdToGameObjectMap[ inNetworkId] = inGameObject;
}

void LinkingContext::RemoveObject(GameObject* inGameObject)
{
	uint32_t network_id = mGameObjectToNetworkIdMap[inGameObject];
	mGameObjectToNetworkIdMap.erase(inGameObject);
	mNetworkIdToGameObjectMap.erase(network_id);
}


template <class T>
void ObjectCreationRegistry::RegisterCreationFunction()
{
	//static_assert(mNameToGameObjectCreationFunctionMap.find(T::kClassId) == mNameToGameObjectCreationFunctionMap.end());
	mNameToGameObjectCreationFunctionMap[T::kClassId] = T::CreateInstance;
}

GameObject* ObjectCreationRegistry::CreateGameObject(uint32_t inClassId)
{
	GameObjectCreationFunc creation_func = mNameToGameObjectCreationFunctionMap[inClassId];
	GameObject* gameObject = creation_func();
	LinkingContext::getInstance().GetNetworkId(gameObject,true);
	return gameObject;
}


void RegisterObjectCreation()
{
	ObjectCreationRegistry::getInstance().RegisterCreationFunction<GameObject>();
	ObjectCreationRegistry::getInstance().RegisterCreationFunction<Person>();
}


void Person::WriteToBitStream(OutputMemoryBitStream& instream) const
{
	instream.Write(x);
	instream.Write(y);
	instream.Write(z);
}

void Person::ReadFromBitStream(InputMemoryBitStream& inStream)
{
	inStream.Read(x);
	inStream.Read(y);
	inStream.Read(z);
}

