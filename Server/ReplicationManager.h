#pragma once
#include "MemoryBitStream.h"
#include <vector>
#include "GameObject.h"
#include "Singleton.h"



enum PacketType
{
	PT_ReplicationData
};

class ReplicationManager :public Singleton<ReplicationManager>
{
public:
	static ReplicationManager& Get()
	{
		static ReplicationManager sInstance;
		return sInstance;
	}

	void ReplicateWorldState(OutputMemoryBitStream& inStream, const std::vector<GameObject*>& inAllObject);

private:
	void ReplicateIntoStream(OutputMemoryBitStream& inStream, GameObject*  inGameObject);
	//LinkingContext* mLinkingContext;
	

};


extern ReplicationManager g_replication_manager;