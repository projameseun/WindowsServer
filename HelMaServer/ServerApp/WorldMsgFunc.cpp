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
    //플레이어가 로그인은했고 이미 캐릭터가 존재하는걸 갖는ㅍ ㅐ킷이고
    //그 캐릭터패킷들을 클라로 보내주는곳 그러기때문에 브로드캐스트는 아직필요없다
    
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

    // 커넥터 세팅해주고
    // 월드에 대기하고 있는 엑터를 하나 만들어준다.
    // 실제 위쪽에 영향을 주지 않겠죠.
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



    // 브로드 캐스트
    // 나와 인접한 모든 유저들에게 쏜다.

    // 현재 존재하는 모든 유저들에게 나의 존재를 알렸다.
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
        PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷

        // 내가 이미 접속해서 이제 들어가 있죠?

        for (auto& _Actor : GetActor)
        {
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // 내가 여기 들어있을 일은 없으니
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
    // 내가 이미 들어갔어요.
    if (false == _World->WaitActorInWorld(_Connecter->GetActor()))
    {
        GameEngineDebug::AssertMsg("if (false == _World->WaitActorInWorld(_Connecter->GetActor()))");
    }

    GameStartPacket Packet;
    Packet.ID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
    _Connecter->Send(Packet);

    // 유저 리스트를 받아온다.
    // 현재 존재하는 모든 유저들에게 나의 존재를 알렸다.
    {
        std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList(2);

        _Connecter->GetActor();

        PlayerUpdateDataPacket Data;
        Data.UpdateID = reinterpret_cast<__int64>(_Connecter->GetPlayer());
        Data.m_State = ActorState::in;
        Data.m_Data.SetData(_Connecter->GetPlayer()->GetPos(), _Connecter->GetPlayer()->GetRot());
        Data.NICKNAME = _Connecter->GetPlayer()->GetPlayerNickName();
        Data.CHARACTERNAME = _Connecter->GetPlayer()->GetPlayerCharacterName();
        // 위치 여기로 등장시켜라.
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

        PlayerUpdatePacket AllActorPacket; // 나에게 모든 다룬 유저들을 알려주는 패킷

        for (auto& _Actor : GetActor)
        {
            // 나의 정보는 나에게 보내는 정보로 들어가면 안된다.
            // 내가 받기는 하겠지만 거기에 내가 또 들어가있을 필요는 없다.
            if (_Actor.get() == _Connecter->GetPlayer())
            {
                continue;
            }

            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPlayer> OtherPlayer = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            PlayerUpdateDataPacket Data;
            Data.UpdateID = reinterpret_cast<__int64>(OtherPlayer.get());
            Data.m_State = ActorState::Update;
            // 여기서 회전값도 같이 보내요.
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
    //        // 내가 여기 들어있을 일은 없으니
    //        std::shared_ptr<ServerMonster> OtherMonster = std::dynamic_pointer_cast<ServerMonster, Actor>(_Actor);
    //        OtherMonster->Setting();
    //        OtherMonster->MonsterData.m_State = ActorState::Update;
    //        AllMonsterPacket.m_MonsterData.push_back(OtherMonster->MonsterData);
    //    }

    //    _Connecter->Send(AllMonsterPacket);
    //}

    //{
    //    std::list<std::shared_ptr<Actor>>& GetActor = _World->GetActorList((int)LogicValue::CollisionLayer::ITEM);

    //    ItemUpdatePacket AllItemPacket; // 나에게 모든 다룬 유저들을 알려주는 패킷

    //    for (auto& _Actor : GetActor)
    //    {
    //        // 내가 여기 들어있을 일은 없으니
    //        std::shared_ptr<ServerItem> OtherItem = std::dynamic_pointer_cast<ServerItem, Actor>(_Actor);
    //        AllItemPacket.m_ItemUpdateDataList.push_back(OtherItem->GetItemData());
    //    }

    //    _Connecter->Send(AllItemPacket);
    //}

 

    int a = 0;


}

void WorldMsgFunc::PlayerUpdate(World* _World, ServerConnecter* _Connecter, ClientPlayerPacket _Packet)
{

    // 여기까지 왔으면
    // 플레이어는 무조건 세팅되어 있어야 하고
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
            PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷
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

                // 내가 여기 들어있을 일은 없으니
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
        PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷
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

            // 내가 여기 들어있을 일은 없으니
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

    // 월드에 있는 모든 유저들에게 나의 죽음을 알려줘야 하니까.
    // 다른 모든 유저들에게 내가 움직였다는 사실을 알려준다. 
    {
        PlayerUpdatePacket AllActorPacket; // 나를 알려주는 패킷
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

            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(AllActorPacket);
        }
    }
}

void WorldMsgFunc::ItemUpdate(World* _World, ItemUpdateData _Packet) 
{
    {
        std::shared_ptr<ServerItem> NewItem = _World->CreateActor<ServerItem>((int)LogicValue::CollisionLayer::ITEM);

        ItemUpdatePacket AllActorPacket; // 나를 알려주는 패킷
        _Packet.UpdateID = reinterpret_cast<__int64>(NewItem.get());
        AllActorPacket.m_ItemUpdateDataList.push_back(_Packet);

        // 아이템의 위치를 세팅해줘야
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

    // 월드에 있는 모든 유저들에게 나의 죽음을 알려줘야 하니까.
      // 다른 모든 유저들에게 내가 움직였다는 사실을 알려준다. 
    {
        // 먹은 유저에게는 특별한 ItemUpdateData 날릴것이냐
        // 아니면 그냥 다 날리고 클라이언트에서 처리할거냐
        // 다 날리고 클라이언트에서 처리.

        ItemUpdatePacket AllActorPacket; // 나를 알려주는 패킷
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
            // 몬스터랑 플레이어가 _Data.UpdateID가 겹칠리가 없는데
            // 선생님이 그냥 코드 복사하다가.
            // 붙어버린거네요.
            if (_Actor.get() == reinterpret_cast<Actor*>(_Data.UpdateID))
            {
                continue;
            }

            // 내가 여기 들어있을 일은 없으니
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

            // 내가 여기 들어있을 일은 없으니
            std::shared_ptr<ServerPlayer> Ptr = std::dynamic_pointer_cast<ServerPlayer, Actor>(_Actor);
            Ptr->GetConnecter()->Send(_MonsterData);
        }
    }
}

void WorldMsgFunc::WorldMoveOk(World* _World, ServerConnecter* _Connect) 
{
    // 이걸 사용한 당사자에게 날리는 처리.
    WorldMoveOKPacket Pacekt;
    _Connect->Send(Pacekt);
}