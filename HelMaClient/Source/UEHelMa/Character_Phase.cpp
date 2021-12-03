// Fill out your copyright notice in the Description page of Project Settings.



#include "Character_Phase.h"
#include "PhaseAnim.h"
#include <ClientToServer.h>
#include "UEServerConnect.h"

ACharacter_Phase* ACharacter_Phase::MainCharacter = nullptr;

ACharacter_Phase::ACharacter_Phase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//애니메이션 클래스 지정
	static ConstructorHelpers::FClassFinder<UPhaseAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Player/BP_PhaseAnim.BP_PhaseAnim_C'"));

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}
}

ACharacter_Phase::~ACharacter_Phase()
{
	
}

void ACharacter_Phase::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = this;

	PhaseAnim = Cast<UPhaseAnim>(GetMesh()->GetAnimInstance());
}


void ACharacter_Phase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacter_Phase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &ACharacter_Phase::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &ACharacter_Phase::MoveSide);
}

void ACharacter_Phase::ServerUpdate(float DeltaTime)
{
	ACharacterMaster::ServerUpdate(DeltaTime);
	
}

void ACharacter_Phase::SingleUpdate(float DeltaTime)
{

}

//이동은 지금은 키보드이지만 추후에 마우스클릭으로 변경될수잇음
void ACharacter_Phase::MoveFront(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}

	//ACharacterMaster::MoveFront(_Scale);
	PhaseAnim->MoveAnim(); 
	//LOG(TEXT("MOveFrontPhase"));


}
void ACharacter_Phase::MoveSide(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}
	//ACharacterMaster::MoveSide(_Scale);
	PhaseAnim->MoveAnim();
	//LOG(TEXT("MOveSidePhase"));
}

void ACharacter_Phase::RotationZ(float _Scale)
{
	//ACharacterMaster::RotationZ(_Scale);

	//LOG(TEXT("RotationZPhase"));

}