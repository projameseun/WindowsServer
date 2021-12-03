// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientPacketFunc.h"
#include "UEServerConnect.h"
#include "UEWorldMsgFunc.h"
#include "Widget_Start.h"
#include <ServerToClientPacketUpdater.h>
#include <ServerToClient.h>
#include <ClientToServer.h>
#include "HelMaGameInstance.h"
ClientPacketFunc::ClientPacketFunc()
{
}

ClientPacketFunc::~ClientPacketFunc()
{
}

void ClientPacketFunc::Init()
{
    STOCPACKETCALLBACK(AccountResultPacket);
    STOCPACKETCALLBACK(LoginResultPacket);
    STOCPACKETCALLBACK(CharacterPacket);
    STOCPACKETCALLBACK(CharacterUpdatePacket);
    STOCPACKETCALLBACK(SelectUpdatePacket);
    STOCPACKETCALLBACK(GameStartPacket);
    STOCPACKETCALLBACK(PlayerUpdateDataPacket);
    STOCPACKETCALLBACK(PlayerUpdatePacket);
    STOCPACKETCALLBACK(MonsterUpdatePacket);
    STOCPACKETCALLBACK(MonsterUpdateDataPacket);
    STOCPACKETCALLBACK(ItemUpdatePacket);
    STOCPACKETCALLBACK(WorldMoveOKPacket);
    STOCPACKETCALLBACK(RankPacket);
    STOCPACKETCALLBACK(PlayerDeathPacket);
}

void ClientPacketFunc::LoginResultPacketProcess(LoginResultPacket _Packet)
{
    if (0 != _Packet.m_Code)
    {
        UEServerConnect::GetInst().m_Login = 0;
        
        LOGERROR(L"Login Error ");
       
    }
    else
    {
        UEServerConnect::GetInst().m_Login = 1;
        LOG(L"PacketCode:%d", _Packet.m_Code);
        LOG(L"Login OK ");

    }
}
void ClientPacketFunc::CharacterPacketProcess(CharacterPacket _Packet)
{
    LOG(L"CharacterPacketProcess");
    //ó���÷��̾ ���������� ������ ���⼭ �÷��̾ ����

    UEServerConnect::GetInst().m_CharacterData = _Packet;
    //UEServerConnect::GetInst().m_CharacterData.ItemDatas.clear();
    //UEServerConnect::GetInst().m_CharacterData.ItemDatas.resize(25);

    //for (size_t i = 0; i < _Packet.ItemDatas.size(); i++)
    //{
    //    UEServerConnect::GetInst().m_CharacterData.ItemDatas[_Packet.ItemDatas[i].InvenOrder] = _Packet.ItemDatas[i];
    //}
    if (_Packet.CHARACTERNAME == L"Kallari")
    {
        LOG(L"KallariStart");

        UHelMaGameInstance::GetInst().SetSelectPlayerName(L"Kallari");
    }

    else if (_Packet.CHARACTERNAME == L"Phase")
    {
        LOG(L"PhaseStart");
        UHelMaGameInstance::GetInst().SetSelectPlayerName(L"Phase");
      
    }
    else if (_Packet.CHARACTERNAME == L"Shinbi")
    {
        LOG(L"ShinbiStart");

        UHelMaGameInstance::GetInst().SetSelectPlayerName(L"Shinbi");
      
    }
       UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::PlayerCreate, _Packet);
 
}

void ClientPacketFunc::CharacterUpdatePacketProcess(CharacterUpdatePacket   _Packet)
{
    int a = 0;
    //����ĳ���͵��� �������մٴ°� Ȯ���Ҽ��մ� 
    //�̰� selectLevel�� �����ߵȴ�.
   //UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::SelectCreate, _Packet);
}

void ClientPacketFunc::SelectUpdatePacketProcess(SelectUpdatePacket   _Packet)
{
    //����ĳ���͵��� �������մٴ°� Ȯ���Ҽ��մ� 
    //�̰� selectLevel�� �����ߵȴ�.
   
    UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::SelectCreate, _Packet);
}


void ClientPacketFunc::GameStartPacketProcess(GameStartPacket _Packet)
{
    UEServerConnect::GetInst().m_GameStart.Exchange(1);

    LOG(L"GameStartPacketProcess");
    //�������� ���� �����ص��ȴٴ°� �޾Ѱ� Ŭ��½��۵ȴ� ����������Ʈ�� ���ư��� ����

}
void ClientPacketFunc::RankPacketProcess(RankPacket _Packet)
{

}

void ClientPacketFunc::AccountResultPacketProcess(AccountResultPacket _Packet)
{
    // �׳� ���⼭ �𸮾� Ŭ���̾�Ʈ �ڵ带 ġ���� ġ�� ������ �ɰ̴ϴ�.
    
   
}



void ClientPacketFunc::PlayerUpdatePacketProcess(PlayerUpdatePacket _Packet)
{
   // LOG(L"PlayerUpdatePacketProcess");

    if (0 == _Packet.m_PlayerData.size())
    {
        // �̰� �°�
        return;
    }

    for (size_t i = 0; i < _Packet.m_PlayerData.size(); i++)
    {
        PlayerUpdateDataPacketProcess(_Packet.m_PlayerData[i]);


    }

}

void ClientPacketFunc::PlayerUpdateDataPacketProcess(PlayerUpdateDataPacket        _Packet)
{
    ActorState State = _Packet.m_State;
   // PlayerUpdateDataPacket Data = _Packet;
    switch (State)
    {
    case ActorState::Wait:
    {
       // UE_LOG(LogTemp, Error, L"PlayerPacket Wait");
        UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::WaitPlayerCreate, _Packet);
        break;
    }
    case ActorState::in:
       // UE_LOG(LogTemp, Error, L"PlayerPacket in");
        UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::WaitPlayerInWorld, _Packet);
        break;
    case ActorState::Update:
        UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::UpdatePlayer, _Packet);
        break;
    case ActorState::Death:
        UE_LOG(LogTemp, Error, L"PlayerPacket Death");
        UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::DeathPlayer, _Packet);
        break;

    default:
        break;
    }

}

void ClientPacketFunc::MonsterUpdateDataPacketProcess(MonsterUpdateDataPacket       _Packet)
{
   
}

void ClientPacketFunc::MonsterUpdatePacketProcess(MonsterUpdatePacket _Packet)
{
  
}


void ClientPacketFunc::ItemUpdatePacketProcess(ItemUpdatePacket _Packet)
{
  
}


void ClientPacketFunc::WorldMoveOKPacketProcess(WorldMoveOKPacket _Packet)
{
   
}

void ClientPacketFunc::PlayerDeathPacketProcess(PlayerDeathPacket _Packet)
{
    UE_LOG(LogTemp, Error, L"ImDeath!!!!!");

    UEServerConnect::GetInst().MsgInsert(&UEWorldMsgFunc::LogOut, _Packet);
}

