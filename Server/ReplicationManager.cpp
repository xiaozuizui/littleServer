#include "ReplicationManager.h"

void ReplicationManager::ReplicateWorldState(OutputMemoryBitStream& inStream, const std::vector<GameObject*>& inAllObject)
{
	
}


void ReplicationManager::ReplicateIntoStream(OutputMemoryBitStream& inStream, GameObject* inGameObject)
{
	//写入  ID
	inStream.Write(LinkingContext::getInstance().GetNetworkId(inGameObject, true));
	//写入  Class
	inStream.Write(inGameObject->GetClassId());
	//写入  数据
	inGameObject->WriteToBitStream(inStream);
	
}


 
//ReplicationManager g_replication_manager = ReplicationManager::Get();