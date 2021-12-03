// Fill out your copyright notice in the Description page of Project Settings.


#include "UEWorldMsgFunc.h"
#include "UECharacterManager.h"
#include "Widget_Select.h"
#include "Widget_CharacterImg.h"
#include <ServerToClient.h>
#include <GameEngineString.h>
#include <LogicValue.h>
#include "CharacterMaster.h"
#include "Character_Kallari.h"
#include "Character_Phase.h"
#include "Character_Shinbi.h"
#include "OtherPlayer.h"
#include "UEServerConnect.h"


UEWorldMsgFunc::UEWorldMsgFunc()
{
}

UEWorldMsgFunc::~UEWorldMsgFunc()
{
}

void UEWorldMsgFunc::SelectCreate(UWorld* _World, SelectUpdatePacket _Packet)
{
    //여기서 캐릭터가 만약에 존재한다면 띄워준다 

    LOG(L"SelectCreate!!!!!!!!!!!!!!!!!!!");

    UWidget_Select::SelectWidgetInst->GetCharacterImg0()->InitCharacterImg();
    UWidget_Select::SelectWidgetInst->GetCharacterImg1()->InitCharacterImg();
    UWidget_Select::SelectWidgetInst->GetCharacterImg2()->InitCharacterImg();
    UWidget_Select::SelectWidgetInst->GetCharacterImg3()->InitCharacterImg();

    UWidget_Select::SelectWidgetInst->HiddentCharacterWidgetImg();
    //InitCharacterImg

    UWidget_Select::SelectWidgetInst->DataSize = _Packet.m_CharacterData.size();

    if (0 != _Packet.m_CharacterData.size())
    {
        for (size_t i = 0; i < _Packet.m_CharacterData.size(); i++)
        {
            if (0 == i)
            {
                UWidget_Select::SelectWidgetInst->SetCreateString
                (_Packet.m_CharacterData[i].NICKNAME.m_String.c_str());

                UWidget_Select::SelectWidgetInst->VisibleCharacterWidgetImg0();
                 if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Kallari")
                 {
                     UWidget_Select::SelectWidgetInst->GetCharacterImg0()->SetCharacterImg((int32)ECharacterName::Kallari);
                 
                 }
                 else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Phase")
                 {
                     UWidget_Select::SelectWidgetInst->GetCharacterImg0()->SetCharacterImg((int32)ECharacterName::Phase);
                 }
                 else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Shinbi")
                 {
                     UWidget_Select::SelectWidgetInst->GetCharacterImg0()->SetCharacterImg((int32)ECharacterName::Shinbi);
                 }

            }
            else if (1 == i)
            {


                UWidget_Select::SelectWidgetInst->SetCreateString1
                (_Packet.m_CharacterData[i].NICKNAME.m_String.c_str());

                UWidget_Select::SelectWidgetInst->VisibleCharacterWidgetImg1();
                if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Kallari")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg1()->SetCharacterImg((int32)ECharacterName::Kallari);

                }
                else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Phase")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg1()->SetCharacterImg((int32)ECharacterName::Phase);
                }
                else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Shinbi")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg1()->SetCharacterImg((int32)ECharacterName::Shinbi);
                }
            }

            else if (2 == i)
            {
                UWidget_Select::SelectWidgetInst->SetCreateString2
                (_Packet.m_CharacterData[i].NICKNAME.m_String.c_str());

                UWidget_Select::SelectWidgetInst->VisibleCharacterWidgetImg2();
                if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Kallari")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg2()->SetCharacterImg((int32)ECharacterName::Kallari);

                }
                else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Phase")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg2()->SetCharacterImg((int32)ECharacterName::Phase);
                }
                else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Shinbi")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg2()->SetCharacterImg((int32)ECharacterName::Shinbi);
                }
            }

            else if (3 == i)
            {
                UWidget_Select::SelectWidgetInst->SetCreateString3
                (_Packet.m_CharacterData[i].NICKNAME.m_String.c_str());

                UWidget_Select::SelectWidgetInst->VisibleCharacterWidgetImg3();
                if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Kallari")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg3()->SetCharacterImg((int32)ECharacterName::Kallari);

                }
                else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Phase")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg3()->SetCharacterImg((int32)ECharacterName::Phase);
                }
                else if (_Packet.m_CharacterData[i].CHARACTERNAME == L"Shinbi")
                {
                    UWidget_Select::SelectWidgetInst->GetCharacterImg3()->SetCharacterImg((int32)ECharacterName::Shinbi);
                }
            }
          
        }
        //UWidget_Select::SelectWidget->
    }
    
}

void UEWorldMsgFunc::PlayerCreate(UWorld* _World, CharacterPacket _Packet)
{
    //AMainActor::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY),0 });

    //UnActorManager::GetInst().ActorManagerInit(&AMainActor::GetInst(), _World);
    //여기서 플레이어의 패킷안에 어떤캐릭터를 저장하고잇는데 그거에따라서 나중에 나오는캐릭터가 다름
    //일단은 그냥 기본캐릭터로 나오게하겟음

 
    LOG(L"PlayerCreate!!!!!!!!!!!!!!!!!!!");
   // ACharacter_Kallari::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY),0 });


   // int a = 0;
  
  
    if(_Packet.CHARACTERNAME == L"Kallari")
    { 
        LOG(L"KallariStart");

        ACharacter_Kallari::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY),0 });
     
      UECharacterManager::GetInst().CharacterManagerInit(&ACharacter_Kallari::GetInst(), _World);
    }
            
    else if (_Packet.CHARACTERNAME == L"Phase")
    {
        LOG(L"PhaseStart");
        ACharacter_Phase::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY),0});
      UECharacterManager::GetInst().CharacterManagerInit(&ACharacter_Phase::GetInst(), _World);
    }
    else if (_Packet.CHARACTERNAME == L"Shinbi")
    {
        LOG(L"ShinbiStart");
     
     
       
        ACharacter_Shinbi::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY),0 });
        UECharacterManager::GetInst().CharacterManagerInit(&ACharacter_Shinbi::GetInst(), _World);
    }
        


}

void UEWorldMsgFunc::WaitPlayerCreate(UWorld* _World, PlayerUpdateDataPacket Data)
{
   

     //UE_LOG(LogTemp, Error, TEXT("WaitPlayerCreate %lld %f %f %f"), Data.UpdateID, Data.m_Data.Pos.x, Data.m_Data.Pos.y, Data.m_Data.Pos.z);
     //여기들어왓을대 플레이어를 뺀다른캐릭터 정보 에 맞게 넣어준다

    int a = 0;

    AOtherPlayer* NewOtherPlayer = UECharacterManager::GetInst().CreateServerManagerWaitObject<AOtherPlayer>
        (ACharacterMaster::GetInst().m_OtherPlayerCreateType, 
            { Data.m_Data.Pos.x,Data.m_Data.Pos.y,90.f }, 
            (int)LogicValue::CollisionLayer::PLAYER,
            Data.UpdateID,Data.CHARACTERNAME.ConstStringPtr());

        if (nullptr != NewOtherPlayer)
        {
            NewOtherPlayer->SetActorScale3D({ 1.f, 1.f, 1.f });
        }
}

void UEWorldMsgFunc::WaitPlayerInWorld(UWorld* _World, PlayerUpdateDataPacket Data)
{
  
    // 없으면 그냥 만들어버리면 되기는 하는데...
    AOtherPlayer* FindPtr = UECharacterManager::GetInst().
        FindIDWaitActor<AOtherPlayer>((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);

    if (nullptr == FindPtr)
    {
        //UE_LOG(LogTemp, Log, TEXT("%f, %f"), Data.m_Data.Pos.x, Data.m_Data.Pos.y);
        AOtherPlayer* NewPlayer = UECharacterManager::GetInst().
            CreateServerManagerObjectToCol<AOtherPlayer>(ACharacterMaster::GetInst().
                m_OtherPlayerCreateType, { Data.m_Data.Pos.x,
                Data.m_Data.Pos.y, 90.f},
                (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID,  
                Data.CHARACTERNAME.ConstStringPtr());

        if (nullptr != NewPlayer)
        {
            NewPlayer->SetActorScale3D({ 1.f, 1.f, 1.f });
        }
        UE_LOG(LogTemp, Error, TEXT("WaitPlayerInWorld if (nullptr == FindPtr) %lld"), Data.UpdateID);
        return;
    }

    AOtherPlayer* PlayerPtr = UECharacterManager::GetInst().WaitActorInActorCol<AOtherPlayer>
        ((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID/*, { 100.0f, 100.0f, 100.0f }, COLTYPE::CT_SPHERE*/
           );

    if (nullptr != PlayerPtr)
    {
        PlayerPtr->SetActorScale3D({ 1.0f, 1.0f, 1.0f });
        PlayerPtr->SetActorLocation({ Data.m_Data.Pos.x, Data.m_Data.Pos.y, 90.f });
    }
    // 이녀석을 꺼놓고 동작하지 못하게 하는 기능이 필요하다.
    // UnActorManager::GetInst().PushIDActor(Data.UpdateID, FindPtr);
}


void UEWorldMsgFunc::UpdatePlayer(UWorld* _World, PlayerUpdateDataPacket Data)
{
  
    AOtherPlayer* FindPtr = UECharacterManager::GetInst().FindIDActor<AOtherPlayer>
        ((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);

    // 혹시나 죽었다고 하더라도 
    if (nullptr == FindPtr)
    {
        //UE_LOG(LogTemp, Error, L"PlayerPacket Update Create %lld", Data.UpdateID);
        AOtherPlayer* NewPlayer = UECharacterManager::GetInst().CreateServerManagerObjectToCol<AOtherPlayer>
            (ACharacterMaster::GetInst().m_OtherPlayerCreateType, 
                { Data.m_Data.Pos.x, Data.m_Data.Pos.y, 90.f }, 
                (int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID, 
                Data.CHARACTERNAME.ConstStringPtr()
                /*, { 100.0f, 100.0f, 100.0f },
                COLTYPE::CT_SPHERE*/);
        if (nullptr != NewPlayer)
        {
            NewPlayer->SetActorScale3D({ 1.f, 1.f, 1.f });
        }
        return;
    }

    FindPtr->PushUpdateData(Data.m_Data);

    // 이렇게 바꿔주고 있단 말이야.
    // FindPtr->SetActorLocation(FVector(Data.m_Data.Pos.x, Data.m_Data.Pos.y, 0.0f));
}

void UEWorldMsgFunc::LogOut(UWorld* _World, PlayerDeathPacket _Packet)
{
    UEServerConnect::GetInst().Close();

    UECharacterManager::GetInst().ActorRelease();

   /* if (nullptr != ULoginScreenWidget::GetInst())
    {
        ULoginScreenWidget::GetInst()->SetVisibility(ESlateVisibility::Visible);
    }

    if (nullptr != UPlayUI::PlayUIInst)
    {
        UPlayUI::PlayUIInst->SetVisibility(ESlateVisibility::Hidden);
    }*/

}

void UEWorldMsgFunc::DeathPlayer(UWorld* _World, PlayerUpdateDataPacket Data)
{
    int a = 0;

    ACharacter* FindActor = UECharacterManager::GetInst().FindIDActor<ACharacter>((int)LogicValue::CollisionLayer::PLAYER, Data.UpdateID);
    if (nullptr == FindActor)
    {
        // 로그 찍어서 이런게 발생한다는걸 기록으로 남기는게 좋아요.
        return;
    }

    FindActor->Destroy();
    // UnActorManager::GetInst().EraseIDActor(Data.UpdateID);
    // FindActor->Destroy();
}