#include "ServerWorldManager.h"
#include "ServerWorld.h"

// Static Var
// Static Func

// constructer destructer
ServerWorldManager::ServerWorldManager() 
{

}

ServerWorldManager::~ServerWorldManager() 
{

}
// member Func

std::shared_ptr<ServerWorld> ServerWorldManager::CreateServerWorld(const WorldData& _Data)
{
	PosToKeyConvert Convert = _Data.Index;
	std::shared_ptr<ServerWorld> World = CreateWorld<ServerWorld>(Convert.ToString());
	
	World->WorldStart();

	return World;
}

