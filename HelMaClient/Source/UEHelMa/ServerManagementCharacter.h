// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include <PacketType.h>
#include <queue>
#include "GameFramework/Character.h"
#include "ServerManagementCharacter.generated.h"

UCLASS()
class UEHELMA_API AServerManagementCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AServerManagementCharacter();

protected:
	std::queue<ActorUpdateData> m_UpdateQueue;

public:
	void PushUpdateData(const ActorUpdateData& _Data)
	{
		m_UpdateQueue.push(_Data);
	}

public:
	__int64 UpdateID;
	class GameCol* m_GameCol;

public:
	void SetGameCol(GameCol* _GameCol)
	{
		m_GameCol = _GameCol;
	}

	void SetUpdateID(__int64 _UpdateID)
	{
		UpdateID = _UpdateID;
	}

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
