#pragma once

#include <stdint.h>
#include <unordered_map>
#include "MemoryBitStream.h"
#include "Singleton.h"


#define PropertyFun(Fun,x) Fun ## x
#define Property(Type,x)\
	private:\
	Type x;\
	public:\
	Type PropertyFun(Get_,x) ()\
	{\
		return x;\
	};\
	void PropertyFun(Set_,x)(Type _x)\
{\
	x = _x;\
}\
private:


#define  CLASS_IDENTIFICATION(inCode,inClass) \
enum{kClassId = inCode};\
virtual uint32_t GetClassId() const {return kClassId;};\
static GameObject* CreateInstance() { return static_cast< GameObject* >(new inClass());};\
//inClass(){ ObjectCreationRegistry::Get().RegisterCreationFunction<inClass>(); };\


class GameObject;

typedef GameObject* (*GameObjectCreationFunc)();



class ObjectCreationRegistry: public Singleton<ObjectCreationRegistry>
{
public:
	
	template<class T> void RegisterCreationFunction();
	GameObject* CreateGameObject(uint32_t inClassId);

private:
	//ObjectCreationRegistry() {};
	std::unordered_map<uint32_t, GameObjectCreationFunc>
		mNameToGameObjectCreationFunctionMap;
};
//ObjectCreationRegistry ObjectCreationRegistry::instance;


class LinkingContext : public Singleton<LinkingContext>
{
public:
	LinkingContext()
	{
		mNextworkId = 1;
	};

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

//void RegisterObjectCreation();


class GameObject
{
public:
	CLASS_IDENTIFICATION('GOBJ',GameObject)

	virtual void WriteToBitStream(OutputMemoryBitStream& instream)const {};
	virtual void ReadFromBitStream(InputMemoryBitStream& inStream){} ;
	//GameObject(){};
	virtual ~GameObject() {}
	//virtual ~GameObject() {};
};

class Person: public GameObject
{
public:
	CLASS_IDENTIFICATION('PERS', Person)
	//std::vector<void*()> GetFunctions;
	void WriteToBitStream(OutputMemoryBitStream& instream) const override;
	void ReadFromBitStream(InputMemoryBitStream& inStream) override;
	
	Property(float, x)
	Property(float, y)
	Property(float, z)


private:
	
	void test()
	{
		
	}
	
};





