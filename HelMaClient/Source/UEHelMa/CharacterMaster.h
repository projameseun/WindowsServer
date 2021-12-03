// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "OtherPlayer.h"
#include "GameFramework/Character.h"
#include "CharacterMaster.generated.h"

UCLASS()
class UEHELMA_API ACharacterMaster : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(Category = Arm, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* Arm;

public:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AOtherPlayer> m_OtherPlayerCreateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector2D MousePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector2D MouseCenter;

private:
	static ACharacterMaster* MasterCharacter;

public:
	static ACharacterMaster& GetInst()
	{
		return *MasterCharacter;
	}

public:
	// Sets default values for this character's properties
	ACharacterMaster();
	~ACharacterMaster();

	FVector MoveVector;
	FVector AttVector;
	FRotator MoveRot;
	float fSpeed;
	float RotSpeed;
	
	bool IsMouseCenter;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void ServerUpdate(float DeltaTime);
	virtual void SingleUpdate(float DeltaTime);

public:
	 void MoveFront(float _Scale);
	 void MoveSide(float _Scale);
	 void RotationZ(float _Scale);

public:
	void MousePosCenterLock(APlayerController* _Con);
	void MouseFree();
};
