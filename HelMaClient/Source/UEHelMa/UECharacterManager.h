// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <map>
#include <set>
#include <list>
#include <GEMath.h>


//ĳ���͵��� �浹ü�� ��� ������ ���� 
/**
 * 
 */
class UEHELMA_API UECharacterManager
{
public:
	static UECharacterManager Inst;

public:
	static UECharacterManager& GetInst()
	{
		return Inst;
	}

private:
	ACharacter* MainCharacter;
	UWorld* MainWorld;
	float4 m_Size;
	FString OtherName;

public:
	int Count;

public:
	ACharacter* GetMainCharacter()
	{
		return MainCharacter;
	}

	void SetOtherName(const FString& _Name) 
	{
		OtherName = _Name;
	}

	FString GetOtherName()
	{
		return OtherName;
	}

public:
	void CharacterManagerInit(ACharacter* _MainCharacter, UWorld* _World);


	// ���� ������ �Լ�.
public:
	std::list<ACharacter*> m_Destroy;

	void ActorRelease();
	void Clear();
	void DestoryRelease();

	std::map<int, TMap<__int64, ACharacter*>> m_AllGameWaitActor;
	template<typename T>
	T* FindIDWaitActor(int _Order, __int64 _ID)
	{
		ACharacter** FindPtr = m_AllGameWaitActor[_Order].Find(_ID);
		if (nullptr != FindPtr)
		{
			return Cast<T>(FindPtr[0]);
		}

		return nullptr;
	}

	template<typename T>
	T* CreateServerManagerWaitObject(TSubclassOf<T> _CreateType, FVector _Pos, int _Order, __int64 _ID,FString _Name)
	{

		if (nullptr != m_AllGameWaitActor[_Order].Find(_ID))
		{
			return nullptr;
		}

		FActorSpawnParameters	tParams;
		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SetOtherName(_Name);
		//ASummonPotal* Summon = GetWorld()->SpawnActor<ASummonPotal>(
		//	SummonClass, vPos, GetActorRotation(), tParams);
		T* NewActor = MainWorld->SpawnActor<T>(_CreateType, _Pos, { 0,0,0 }, tParams);
		if (_ID == -1)
		{
			_ID = reinterpret_cast<__int64>(NewActor);
		}

		// -1�̸� Ŭ���̾�Ʈ������ �����Ǵ� ���� �ڽ��� �ּҰ� �����Ŷ�� �̾߱�ϱ�.
		NewActor->SetUpdateID(_ID);

		m_AllGameWaitActor[_Order].Add(_ID, NewActor);

		return NewActor;
	}

	// Player Destroy�Ǵ°� �ƴϰ� �ڸ��� �ű�°� ���̶�.
	void EraseServerManagerWaitObject(int _Order, __int64 _ID)
	{
		ACharacter** Actor = m_AllGameWaitActor[_Order].Find(_ID);
		if (nullptr == Actor)
		{
			return;
		}


		m_AllGameWaitActor[_Order].Remove(_ID);
	}

	// �浹ü ����鼭 �־��ִ°�.
	template<typename T>
	T* WaitActorInActorCol(int _Order, __int64 _ID/*, float4 _Scale*//*, COLTYPE _Type*/)
	{
		T* FindActor = FindIDWaitActor<T>(_Order, _ID);
		if (nullptr != FindActor)
		{
			UE_LOG(LogTemp, Error, TEXT("WaitActorInActorCol(%lld)"), _ID);
			EraseServerManagerWaitObject(_Order, _ID);
			m_AllGameActor[_Order].Add(_ID, FindActor);
			//GameCol* GetPtr = InsertCollison(std::make_shared<GameCol>(_Type, _Order, FindActor), _Scale);
			//FindActor->SetGameCol(GetPtr);
		}
		return FindActor;
	}



public:


	//       order                UpdateId ������Ʈ
	std::map<int, TMap<__int64, ACharacter*>> m_AllGameActor;

	template<typename T>
	T* FindIDActor(int _Order, __int64 _ID)
	{
		ACharacter** FindPtr = m_AllGameActor[_Order].Find(_ID);
		if (nullptr != FindPtr)
		{
			return Cast<T>(FindPtr[0]);
		}
		return nullptr;
	}

	template<typename T>
	T* CreateServerManagerObject(TSubclassOf<T> _CreateType, FVector _Pos, int _Order, __int64 _ID,FString _Name)
	{
		if (nullptr != m_AllGameActor[_Order].Find(_ID))
		{
			UE_LOG(LogTemp, Error, TEXT("if (nullptr != m_AllGameActor[_Order].Find(_ID)), %d, %d"), _Order, _ID);
			return nullptr;
		}

		FActorSpawnParameters	tParams;
		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SetOtherName(_Name);

		T* NewActor = MainWorld->SpawnActor<T>(_CreateType, _Pos, { 0,0,0 },tParams);

		if (nullptr == NewActor)
		{
			UE_LOG(LogTemp, Error, TEXT("nullptr == NewActor %d, %d"), _Order, _ID);
		}

		if (_ID == -1)
		{
			_ID = reinterpret_cast<__int64>(NewActor);
		}

		// -1�̸� Ŭ���̾�Ʈ������ �����Ǵ� ���� �ڽ��� �ּҰ� �����Ŷ�� �̾߱�ϱ�.
		NewActor->SetUpdateID(_ID);

		m_AllGameActor[_Order].Add(_ID, NewActor);

		return NewActor;
	}

	template<typename T>
	T* CreateServerManagerObjectToCol(TSubclassOf<T> _CreateType, FVector _Pos, int _Order, __int64 _ID,FString _Name/*, COLTYPE _Type*/)
	{
		T* NewActor = CreateServerManagerObject(_CreateType, _Pos, _Order, _ID, _Name);
		if (nullptr != NewActor)
		{
		/*	GameCol* GetPtr = InsertCollison(std::make_shared<GameCol>(_Type, _Order, NewActor), _Scale);
			NewActor->SetGameCol(GetPtr);*/
		}
		return NewActor;
	}

	void EraseServerManagerObject(int _Order, __int64 _ID)
	{
		// �������� ã�ƿ��� ����̳׿�.
		ACharacter** Actor = m_AllGameActor[_Order].Find(_ID);
		if (nullptr == Actor)
		{
			UE_LOG(LogTemp, Error, TEXT("Server Erase Fail if (nullptr == Actor) %d %lld"), _Order, _ID);
			return;
		}

		//// �浹ü�� ���� ������� �մϴ�.
		//std::map<AActor*, std::shared_ptr<GameCol>>::iterator FindIter = m_ColMap[_Order].find(Actor[0]);
		//if (m_ColMap[_Order].end() != FindIter)
		//{
		//	FindIter->second->Death();
		//}


		UE_LOG(LogTemp, Error, TEXT("Server Erase OK %d %lld"), _Order, _ID);
		m_AllGameActor[_Order].Remove(_ID);
	}

public:
	UECharacterManager();
	~UECharacterManager();
};
