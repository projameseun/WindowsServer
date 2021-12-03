// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "CharacterMaster.h"
#include "Character_Phase.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API ACharacter_Phase : public ACharacterMaster
{
	GENERATED_BODY()

	class UPhaseAnim* PhaseAnim;

public:
	ACharacter_Phase();
	~ACharacter_Phase();

private:
	static ACharacter_Phase* MainCharacter;

public:
	static ACharacter_Phase& GetInst()
	{
		return *MainCharacter;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void ServerUpdate(float DeltaTime)	override;
	virtual void SingleUpdate(float DeltaTime)	override;

public:
	 void MoveFront(float _Scale)  ;
	 void MoveSide(float _Scale) ;
	 void RotationZ(float _Scale) ;
	
};
