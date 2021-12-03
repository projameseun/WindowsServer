// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Kallari.h"
#include "KallariAnim.h"
#include <ClientToServer.h>
#include "UEServerConnect.h"

ACharacter_Kallari* ACharacter_Kallari::MainCharacter = nullptr;

ACharacter_Kallari::ACharacter_Kallari()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//애니메이션 클래스 지정
	static ConstructorHelpers::FClassFinder<UKallariAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Player/BP_KallariAnim.BP_KallariAnim_C'"));

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}


}

ACharacter_Kallari::~ACharacter_Kallari()
{
}

void ACharacter_Kallari::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = this;
	
	KallariAnim = Cast<UKallariAnim>(GetMesh()->GetAnimInstance());
 }


void ACharacter_Kallari::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacter_Kallari::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &ACharacter_Kallari::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &ACharacter_Kallari::MoveSide);
}

void ACharacter_Kallari::ServerUpdate(float DeltaTime)
{
	ACharacterMaster::ServerUpdate(DeltaTime);
}

void ACharacter_Kallari::SingleUpdate(float DeltaTime)
{

}

//이동은 지금은 키보드이지만 추후에 마우스클릭으로 변경될수잇음
void ACharacter_Kallari::MoveFront(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}
	//ACharacterMaster::MoveFront(_Scale);
	//LOG(TEXT("MoveKallariAnimFront"));

	KallariAnim->MoveAnim();
	
}
void ACharacter_Kallari::MoveSide(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}

	//ACharacterMaster::MoveSide(_Scale);

	//LOG(TEXT("MoveSideKallairSide"));
	KallariAnim->MoveAnim();
}

void ACharacter_Kallari::RotationZ(float _Scale)
{
	//ACharacterMaster::RotationZ(_Scale);

	//LOG(TEXT("RotationZKallair"));
}