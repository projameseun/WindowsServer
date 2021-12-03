#pragma once
// #include <ClientToServer.h>
#include <GameEngineMemory.h>
#include <vector>
#include <LogicConnecter.h>


// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
class DBConnecter;
class DBTask;
class LoginPacket;
class SelectCharacterPacket;
class StartCharacterPacket;
class ServerConnecter;
class CharacterTableData;
class DeleteCharacterPacket;
class ItemTableData;
class DbTaskFunc
{
public:
    static void LoginSelectProcess(DBConnecter* Connecter, DBTask* _Ptr, LoginPacket _Data, ServerConnecter* _Socket);
    static void SelectCharacterProcess(DBConnecter* Connecter, DBTask* _Ptr, ServerConnecter* _Socket);
    static void StartCharacterProcess(DBConnecter* Connecter, DBTask* _Ptr, StartCharacterPacket _Data, ServerConnecter* _Socket);
    static void DeleteCharacterProcess(DBConnecter* Connecter, DBTask* _Ptr, DeleteCharacterPacket _Data, ServerConnecter* _Socket);
    static void DisConnectDataUpdateProcess(DBConnecter* Connecter, DBTask* _Ptr, std::shared_ptr<CharacterTableData> _CharacterData, std::vector<std::shared_ptr<ItemTableData>> _ItemsData, std::vector<ITEMDBCHECKTYPE> _ItemCheck);
    // DB요청의 결과를 어떻게 처리할지를 결정하는 함수들을 모아놓을 겁니다.
};

