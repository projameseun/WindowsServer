// Fill out your copyright notice in the Description page of Project Settings.


#include "UECharacterManager.h"
#include <map>
#include <set>
#include <list>
#include <GEMath.h>
#include <ClientToServer.h>
#include "UEServerConnect.h"



UECharacterManager::UECharacterManager() : MainCharacter(nullptr) 
{
	Count = 0;
}

UECharacterManager::~UECharacterManager()
{
}

UECharacterManager UECharacterManager::Inst;

void UECharacterManager::Clear()
{
	UE_LOG(LogTemp, Error, TEXT("UECharacterManager::Clear()"));

	m_Destroy.clear();
	m_AllGameActor.clear();
	//m_ColMap.clear();
}

void UECharacterManager::ActorRelease()
{
	for (auto& _Var : m_AllGameActor)
	{

		TMap<__int64, ACharacter*>& Characters = _Var.second;

		//if (0 >= Actors.Num())
		//{
		//	continue;
		//}

		for (auto& Entry : Characters)
		{
			UE_LOG(LogTemp, Error, TEXT("%s Hidden"), *Entry.Value->GetName());
			Entry.Value->SetHidden(true);
			m_Destroy.push_back(Entry.Value);
		}
	}

	//m_AllGameActor.clear();
	//m_ColMap.clear();

	//Clear();
}

void UECharacterManager::DestoryRelease()
{
	for (auto& _Actor : m_Destroy)
	{
		_Actor->Destroy();
	}

	m_Destroy.clear();
}

void UECharacterManager::CharacterManagerInit(ACharacter* _MainCharacter, UWorld* _World)
{
	//ĳ���͸� ����ðŰ� ��ĳ���͸� �־��ݴϴ�
	MainCharacter = _MainCharacter;

	//���带�־��ִ������� ���߿����ͳ� �ٸ�ĳ����,actor���� ���带 �˾ƾ� �浹ü�� ������վ
	//
	
	//_MainCharacter->GetWorld();
	MainWorld = _MainCharacter->GetWorld();

	//�������� �غ�̴ٰ� �����ϴ�
	ClientReadyPacket NewPacket;
	NewPacket.m_Code = 1;
	UEServerConnect::GetInst().Send(NewPacket);

	Count++;

	LOG(L"%d", Count);

}
