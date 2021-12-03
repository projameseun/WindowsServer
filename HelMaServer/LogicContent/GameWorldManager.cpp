#include "GameWorldManager.h"
#include <GameEngineDebug.h>
#include "GameWorld.h"

// Static Var
// Static Func

// constructer destructer
GameWorldManager::GameWorldManager() 
{

}

GameWorldManager::~GameWorldManager()
{

}
// member Func
//
//void GameWorldManager::Init() 
//{
//	//CreateGameWorld({ 0,0 }, {8, 6});
//	//CreateGameWorld({ 1,0 }, { 8, 6 });
//	//CreateGameWorld({ 2,0 }, { 20, 15 });
//	//CreateGameWorld({ 0,1 }, { 8, 8 });
//	//CreateGameWorld({ 1,1 }, { 11, 11 });
//	//CreateGameWorld({ 2,1 }, { 8, 6 });
//	//CreateGameWorld({ 0,2 }, { 20, 22 });
//	//CreateGameWorld({ 1,2 }, { 8, 15 });
//	//CreateGameWorld({ 2,2 }, { 15, 5 });
//}
//
////std::shared_ptr<GameWorld> GameWorldManager::CreateGameWorld(const Posfloat4& _Pos, const Sizefloat4& _Size)
////{
////	//PosToKeyConvert Key = _Pos;
////
////	//if (nullptr !=  FindWorld(Key))
////	//{
////	//	GameEngineDebug::AssertMsg("if (nullptr !=  FindWorld(Key)) CreateMapError");
////	//}
////
////	//std::shared_ptr<GameWorld> m_World(new GameWorld());
////	//m_World->SetSize(_Size);
////	//m_WorldMap.insert(std::map<__int64, std::shared_ptr<GameWorld>>::value_type(Key.Key, m_World));
////	//return m_World;
////}
////
////std::shared_ptr<GameWorld> GameWorldManager::FindWorld(const Posfloat4& _Pos) 
////{
////	return FindWorld(PosToKeyConvert(_Pos));
////}
////
////std::shared_ptr<GameWorld> GameWorldManager::FindWorld(const PosToKeyConvert& _Key) 
////{
////	if (m_WorldMap.end() == m_WorldMap.find(_Key.Key))
////	{
////		return nullptr;
////	}
////	return m_WorldMap[_Key.Key];
////}

void GameWorldManager::UpdateCheck(const Posfloat4& _Pos) 
{
	PosToKeyConvert Key = _Pos;
	WorldManager::UpdateCheck(Key.ToString());
}
