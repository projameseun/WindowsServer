// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterMaster.h"
#include "Character_Kallari.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API ACharacter_Kallari : public ACharacterMaster
{
	GENERATED_BODY()

private:
	class UKallariAnim* KallariAnim;

public:
	ACharacter_Kallari();
	~ACharacter_Kallari();

private:
	static ACharacter_Kallari* MainCharacter;

public:
	static ACharacter_Kallari& GetInst()
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
	virtual void ServerUpdate(float DeltaTime) override;
	virtual void SingleUpdate(float DeltaTime) override;

private:
	 void MoveFront(float _Scale) ;
	 void MoveSide(float _Scale)  ;
	 void RotationZ(float _Scale) ;

};
