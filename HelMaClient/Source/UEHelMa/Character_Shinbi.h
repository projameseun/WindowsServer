// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "CharacterMaster.h"
#include "Character_Shinbi.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API ACharacter_Shinbi : public ACharacterMaster
{
	GENERATED_BODY()


	class UShinbiAnim* ShinbiAnim;

public:
	ACharacter_Shinbi();
	~ACharacter_Shinbi();

private:
	static ACharacter_Shinbi* MainCharacter;

public:
	static ACharacter_Shinbi& GetInst()
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
	virtual void ServerUpdate(float DeltaTime)override;
	virtual void SingleUpdate(float DeltaTime)override;

public:
	 void MoveFront(float _Scale) ;
	 void MoveSide(float _Scale) ;
	 void RotationZ(float _Scale) ;
	
};
