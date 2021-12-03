// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "ServerManagementCharacter.h"
#include "OtherPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API AOtherPlayer : public AServerManagementCharacter
{
	GENERATED_BODY()

public:
	class UPhaseAnim* PhaseAnim;
	class UKallariAnim* KallariAnim;
	class UShinbiAnim* ShinAnim;

public:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMesh* KalliMesh;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMesh* ShinbiMesh;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMesh* PhaseMesh;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<USkeletalMesh*> CharacterMesh;

	UPROPERTY(Category = Class, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UClass* PhaseClass;

	UPROPERTY(Category = Class, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UClass* KallariClass;

	UPROPERTY(Category = Class, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UClass* ShinbiClass;

	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UClass*> CharacterAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString CharacterOtherName;
	



public:
	AOtherPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Unregisters from NetworkPrediction System
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	void OtherPlayerUpdate(float _DelTaTime);
	void ActorEnd();

	void CharacterName(const FString& _Name);
	
};
