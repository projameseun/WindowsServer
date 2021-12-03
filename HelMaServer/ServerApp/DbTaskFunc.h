#pragma once
// #include <ClientToServer.h>
#include <GameEngineMemory.h>
#include <vector>
#include <LogicConnecter.h>


// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
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
    // DB��û�� ����� ��� ó�������� �����ϴ� �Լ����� ��Ƴ��� �̴ϴ�.
};

