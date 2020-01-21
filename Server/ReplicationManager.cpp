#include "ReplicationManager.h"

void ReplicationManager::ReplicateWorldState(OutputMemoryBitStream& inStream, const std::vector<GameObject*>& inAllObject)
{
	
}


void ReplicationManager::ReplicateIntoStream(OutputMemoryBitStream& inStream, GameObject* inGameObject)
{
	//д��  ID
	inStream.Write(LinkingContext::getInstance().GetNetworkId(inGameObject, true));
	//д��  Class
	inStream.Write(inGameObject->GetClassId());
	//д��  ����
	inGameObject->WriteToBitStream(inStream);
	
}


 
//ReplicationManager g_replication_manager = ReplicationManager::Get();