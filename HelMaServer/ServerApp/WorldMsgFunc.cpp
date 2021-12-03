#include "WorldMsgFunc.h"
#include <World.h>
#include <LogicValue.h>
#include "ServerActor.h"
#include "ServerPlayer.h"
#include "ServerMonster.h"
#include "ServerItem.h"
#include "ServerBullet.h"
#include <GameWorld.h>
#include <ServerToClient.h>
#include <ItemTable.h>
#include <iostream>

void WorldMsgFunc::SelectPlayerCreate(World* _World, ServerConnecter* _Connecter)
{
    //�÷��̾ �α������߰� �̹� ĳ���Ͱ� �����ϴ°� ���¤� ��Ŷ�̰�
    //�� ĳ������Ŷ���� Ŭ��� �����ִ°� �׷��⶧���� ��ε�ĳ��Ʈ�� �����ʿ����
    
   std::vector<std::shared_ptr<CharacterTableData>> Data = _Connecter->GetCharacterDatas();
    
    std::vector<CharacterPacket> NewCharacterPacket;

    NewCharacterPacket.resize(Data.size());

    SelectUpdatePacket UpdateCharactetPacket;

    for (size_t i = 0; i < Data.size(); i++)
    {
        NewCharacterPacket[i].PID = Data[i]->PID;
        NewCharacterPacket[i].NAME = GameEngineString::GlobalSetConvertMultiByteString(Data[i]->Name);
        NewCharacterPacket[i].NICKNAME = GameEngineString::GlobalSetConvertMultiByteString(Data[i]->NickName);
        NewCharacterPacket[i].CHARACTERNAME = GameEngineString::GlobalSetConvertMultiByteString(Data[i]->CharacterName);
        NewCharacterPacket[i].EndIndex = GameEngineString::GlobalSetConvertMultiByteString(Data[i]->EndIndex);
        NewCharacterPacket[i].LastX = Data[i]->LastX;
        NewCharacterPacket[i].LastY = Data[i]->LastY;
        NewCharacterPacket[i].MaxHp = Data[i]->MAXHP;
        NewCharacterPacket[i].Hp = Data[i]->HP;
        NewCharacterPacket[i].Att = Data[i]->ATT;

        UpdateCharactetPacket.m_CharacterData.push_back(NewCharacterPacket[i]);
        
    }
    
    if (SOCKET_ERROR == _Connecter->Send(UpdateCharactetPacket))
    {
        int a = 0;
    }

}

void WorldMsgFunc::WaitPlayerCreate(World* _World, ServerConnecter* _Connecter)
{

    // Ŀ���� �������ְ�
    // ���忡 ����ϰ� �ִ� ���͸� �ϳ� ������ش�.
    // ���� ���ʿ� ������ ���� �ʰ���.
    std::shared_ptr<ServerPlayer> NewPlayer = _World->CreateWaitActor<ServerPlayer>((int)LogicValue::CollisionLayer::PLAYER);
    NewPlayer->SetPos({ _Connecter->GetCharacterData()->LastX , _Connecter->GetCharacterData()->LastY });
    NewPlayer->SetConnecter(_Connecter);
    NewPlayer->SetPlayeCharacterName(GameEngineString::GlobalSetConvertMultiByteString(_Connecter->GetCharacterData()->CharacterName));
    NewPlayer->SetPlayerNickName (GameEngineString::GlobalSetConvertMultiByteString(_Connecter->GetCharacterData()->NickName));
    _Connecter->SetActor(NewPlayer);
    _Connecter->SetPlayer(NewPlayer.get());



    std::shared_ptr<CharacterTableData> _Data = _Connecter->GetCharacterData();

    CharacterPacket NewCharacterPacket;
    NewCharacterPacket.UpdateID = reinterpret_cast<__int64>(NewPlayer.get());
    NewCharacterPacket.NAME = GameEngineString::GlobalSetConvertMultiByteString(_Data->Name);
    NewCharacterPacket.NICKNAME = GameEngineString::GlobalSetConvertMultiByteString(_Data->NickName);
    NewCharacterPacket.CHARACTERNAME = GameEngineString::GlobalSetConvertMultiByteString(_Data->CharacterName);
    NewCharacterPacket.EndIndex = GameEngineString::GlobalSetConvertMultiByteString(_Data->EndIndex);
    NewCharacterPacket.LastX = _Data->LastX;
    NewCharacterPacket.LastY = _Data->LastY;
    NewCharacterPacket.MaxHp = _Data->MAXHP;
    NewCharacterPacket.Hp = _Data->HP;
    NewCharacterPacket.Att = _Data->ATT;

    //std::cout << NewCharacterPacket.UpdateID << std::endl;

    //std::vector<std::shared_ptr<ItemTableData>>& _ItemData = _Connecter->GetItemsDataRef();

    //for (size_t i = 0; i < _ItemData.size(); i++)
    //{
    //    if (nullptr == _ItemData[i])
    //    {
    //        continue;
    //    }

    //    //ItemData Data;
    //    //// Data.Name = L"FASDFSADF";
    //    //Data.Name = GameEngineString::GlobalSetConvertMultiByteString(_ItemData[i]->Name, CP_UTF8);
    //    //Data.InvenOrder = _ItemData[i]->InvenOrder;
    //    //Data.Type = _ItemData[i]->Type;
    //    //Data.Count = _ItemData[i]->Count;   
    //    //Data.IconResData = _ItemData[i]->IconResData;

    //    //NewCharacterPacket.ItemDatas.push_back(Data);
    //}

    //auto ddd = NewCharacterPacket.Serialize();
    //CharacterPacket tmp;
    //tmp.DeSerialize(ddd);

    if (SOCKET_ERROR == _Connecter->Send(NewCharacterPacket))
    {
        int a = 0;
    }



    // ��ε� ĳ��Ʈ
    // ���� ������ ��� �����鿡�� ���.

    // ���� �����ϴ� ��� �����鿡�� ���� ���縦 �˷ȴ�.
    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
    {
        PlayerUpdateDataPacket Data;
        Data.UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
        Data.m_State = ActorState::Wait;
        Data.m_Data.Pos = _Connecter->GetPlayer()->GetPos();
        Data.NICKNAME = _Connecter->GetPlayer()->GetPlayerNickName();
        Data.CHARACTERNAME = _Connecter->GetPlayer()->GetPlayerCharacterName();
       for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

         
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            if (0 == Ptr->GetConnecter()->Send(Data))
            {
                int a = 0;
            }
        }
    }

    {
        PlayerUpdatePacket AllActorPacket; // ���� �˷��ִ� ��Ŷ

        // ���� �̹� �����ؼ� ���� �� ����?

        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // ���� ���� ������� ���� ������
            std::shared_ptr<ServerPlayer> OtherPlayer = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            PlayerUpdateDataPacket Data;
            Data.UpdateID = reinterpret_cast<__int64>(OtherPlayer.get());
            Data.m_State = ActorState::Update;
            Data.m_Data.SetData(OtherPlayer->GetPos(), OtherPlayer->GetRot());
            Data.NICKNAME =OtherPlayer->GetPlayerNickName();
            Data.CHARACTERNAME = OtherPlayer->GetPlayerCharacterName();
            AllActorPacket.m_PlayerData.push_back(Data);
        }

        NewPlayer->GetConnecter()->Send(AllActorPacket);
    }


    int a = 0;


}

void WorldMsgFunc::WaitPlayerInWorld(World* _World, ServerConnecter* _Connecter) 
{
    // ���� �̹� �����.
    if (false == _World->WaitActorInWorld(_Connecter->GetActor()))
    {
        GameEngineDebug::AssertMsg("if (false == _World->WaitActorInWorld(_Connecter->GetActor()))");
    }

    GameStartPacket Packet;
    Packet.ID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
    _Connecter->Send(Packet);

    // ���� ����Ʈ�� �޾ƿ´�.
    // ���� �����ϴ� ��� �����鿡�� ���� ���縦 �˷ȴ�.
    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);

        _Connecter->GetActor();

        PlayerUpdateDataPacket Data;
        Data.UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
        Data.m_State = ActorState::in;
        Data.m_Data.SetData(_Connecter->GetPlayer()->GetPos(), _Connecter->GetPlayer()->GetRot());
        Data.NICKNAME = _Connecter->GetPlayer()->GetPlayerNickName();
        Data.CHARACTERNAME = _Connecter->GetPlayer()->GetPlayerCharacterName();
        // ��ġ ����� ������Ѷ�.
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(Data);
        }
    }

    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::PLAYER);

        PlayerUpdatePacket AllActorPacket; // ������ ��� �ٷ� �������� �˷��ִ� ��Ŷ

        for (auto& _Actor : GetActor)
        {
            // ���� ������ ������ ������ ������ ���� �ȵȴ�.
            // ���� �ޱ�� �ϰ����� �ű⿡ ���� �� ������ �ʿ�� ����.
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // ���� ���� ������� ���� ������
            std::shared_ptr<ServerPlayer> OtherPlayer = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            PlayerUpdateDataPacket Data;
            Data.UpdateID = reinterpret_cast<__int64>(OtherPlayer.get());
            Data.m_State = ActorState::Update;
            // ���⼭ ȸ������ ���� ������.
            Data.m_Data.SetData(OtherPlayer->GetPos(), OtherPlayer->GetRot());
            Data.NICKNAME = OtherPlayer->GetPlayerNickName();
            Data.CHARACTERNAME = OtherPlayer->GetPlayerCharacterName();
            AllActorPacket.m_PlayerData.push_back(Data);
        }

        _Connecter->Send(AllActorPacket);
    }


    //{
    //    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::MONSTER);

    //    MonsterUpdatePacket AllMonsterPacket; 

    //    for (auto& _Actor : GetActor)
    //    {
    //        // ���� ���� ������� ���� ������
    //        std::shared_ptr<ServerMonster> OtherMonster = std::dynamic_pointer_cast<ServerMonster, Actor>(_Actor);
    //        OtherMonster->Setting();
    //        OtherMonster->MonsterData.m_State = ActorState::Update;
    //        AllMonsterPacket.m_MonsterData.push_back(OtherMonster->MonsterData);
    //    }

    //    _Connecter->Send(AllMonsterPacket);
    //}

    //{
    //    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::ITEM);

    //    ItemUpdatePacket AllItemPacket; // ������ ��� �ٷ� �������� �˷��ִ� ��Ŷ

    //    for (auto& _Actor : GetActor)
    //    {
    //        // ���� ���� ������� ���� ������
    //        std::shared_ptr<ServerItem> OtherItem = std::dynamic_pointer_cast<ServerItem, Actor>(_Actor);
    //        AllItemPacket.m_ItemUpdateDataList.push_back(OtherItem->GetItemData());
    //    }

    //    _Connecter->Send(AllItemPacket);
    //}

 

    int a = 0;


}

void WorldMsgFunc::PlayerUpdate(World* _World, ServerConnecter* _Connecter, ClientPlayerPacket _Packet)
{

    // ������� ������
    // �÷��̾�� ������ ���õǾ� �־�� �ϰ�
    if (nullptr == _Connecter->GetPlayer())
    {
        GameEngineDebug::AssertMsg("if (nullptr == _Connecter->GetPlayer())");
    }

    ActorState State = _Packet.m_State;

    switch (State)
    {
    case ActorState::Update:

         //std::cout << "Count " << _Packet.ActorData.Count << std::endl;
        _Connecter->GetPlayer()->PushUpdateData(_Packet.ActorData);
        {
            PlayerUpdatePacket AllActorPacket; // ���� �˷��ִ� ��Ŷ
            AllActorPacket.m_PlayerData.resize(1);
            AllActorPacket.m_PlayerData[0].m_State = ActorState::Update;
            AllActorPacket.m_PlayerData[0].m_Data = _Packet.ActorData;
            AllActorPacket.m_PlayerData[0].UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
            std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
            for (auto& _Actor : GetActor)
            {
                if (_Actor.get() == _Connecter->GetPlayer())
                {
                    continue;
                }

                // ���� ���� ������� ���� ������
                std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
                Ptr->GetConnecter()->Send(AllActorPacket);
            }
        }
        break;
    case ActorState::Att:
    {
        int a = 0;
        _Connecter->GetPlayer()->PushUpdateData(_Packet.ActorData);


        break;
    }
    case ActorState::WorldMove:
    {
        PlayerUpdatePacket AllActorPacket; // ���� �˷��ִ� ��Ŷ
        AllActorPacket.m_PlayerData.resize(1);
        AllActorPacket.m_PlayerData[0].m_State = ActorState::WorldMove;
        AllActorPacket.m_PlayerData[0].UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // ���� ���� ������� ���� ������
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
        break;
    case ActorState::Death:
        break;
    default:
        break;
    }




}

void WorldMsgFunc::PlayerDeath(World* _World, __int64 _ID) 
{

    // ���忡 �ִ� ��� �����鿡�� ���� ������ �˷���� �ϴϱ�.
    // �ٸ� ��� �����鿡�� ���� �������ٴ� ����� �˷��ش�. 
    {
        PlayerUpdatePacket AllActorPacket; // ���� �˷��ִ� ��Ŷ
        AllActorPacket.m_PlayerData.resize(1);
        AllActorPacket.m_PlayerData[0].m_State = ActorState::Death;
        AllActorPacket.m_PlayerData[0].UpdateID = _ID;
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == reinterpret_cast<Actor*>(_ID))
            {
                continue;
            }

            // ���� ���� ������� ���� ������
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
}

void WorldMsgFunc::ItemUpdate(World* _World, ItemUpdateData _Packet) 
{
    {
        std::shared_ptr<ServerItem> NewItem = _World->CreateActor<ServerItem>((int)LogicValue::CollisionLayer::ITEM);

        ItemUpdatePacket AllActorPacket; // ���� �˷��ִ� ��Ŷ
        _Packet.UpdateID = reinterpret_cast<__int64>(NewItem.get());
        AllActorPacket.m_ItemUpdateDataList.push_back(_Packet);

        // �������� ��ġ�� ���������
        NewItem->SetPos(_Packet.CurPos);

        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
}

void WorldMsgFunc::ItemDeath(World* _World, ItemUpdateData _Packet)
{
    if (_Packet.m_State != ActorState::Death)
    {
        int a = 0;
    }

    // ���忡 �ִ� ��� �����鿡�� ���� ������ �˷���� �ϴϱ�.
      // �ٸ� ��� �����鿡�� ���� �������ٴ� ����� �˷��ش�. 
    {
        // ���� �������Դ� Ư���� ItemUpdateData �������̳�
        // �ƴϸ� �׳� �� ������ Ŭ���̾�Ʈ���� ó���Ұų�
        // �� ������ Ŭ���̾�Ʈ���� ó��.

        ItemUpdatePacket AllActorPacket; // ���� �˷��ִ� ��Ŷ
        AllActorPacket.m_ItemUpdateDataList.push_back(_Packet);
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
}

void WorldMsgFunc::MonsterUpdate(World* _World, MonsterUpdateDataPacket _Data) 
{
    {
        _Data.m_State = ActorState::Update;
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            // ���Ͷ� �÷��̾ _Data.UpdateID�� ��ĥ���� ���µ�
            // �������� �׳� �ڵ� �����ϴٰ�.
            // �پ�����ų׿�.
            if (_Actor.get() == reinterpret_cast<Actor*>(_Data.UpdateID))
            {
                continue;
            }

            // ���� ���� ������� ���� ������
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(_Data);
        }
    }
}

void WorldMsgFunc::MonsterDeath(World* _World, MonsterUpdateDataPacket _MonsterData)
{
    {
        ItemUpdateData NewData;
        NewData.CurPos = _MonsterData.m_Data.Pos;
        NewData.m_State = ActorState::Update;
        _World->MsgInsert(&WorldMsgFunc::ItemUpdate, NewData);

        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);
        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == reinterpret_cast<Actor*>(_MonsterData.UpdateID))
            {
                continue;
            }

            // ���� ���� ������� ���� ������
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(_MonsterData);
        }
    }
}

void WorldMsgFunc::WorldMoveOk(World* _World, ServerConnecter* _Connect) 
{
    // �̰� ����� ����ڿ��� ������ ó��.
    WorldMoveOKPacket Pacekt;
    _Connect->Send(Pacekt);
}