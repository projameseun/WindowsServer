// Fill out your copyright notice in the Description page of Project Settings.

#include "Character_Shinbi.h"
#include "ShinbiAnim.h"
#include <ClientToServer.h>
#include "UEServerConnect.h"

ACharacter_Shinbi* ACharacter_Shinbi::MainCharacter = nullptr;

ACharacter_Shinbi::ACharacter_Shinbi()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//애니메이션 클래스 지정
	static ConstructorHelpers::FClassFinder<UShinbiAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Player/BP_ShinbiAnim.BP_ShinbiAnim_C'"));

	if (AnimAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}
}

ACharacter_Shinbi::~ACharacter_Shinbi()
{

}

void ACharacter_Shinbi::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = this;

	ShinbiAnim = Cast<UShinbiAnim>(GetMesh()->GetAnimInstance());
}


void ACharacter_Shinbi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (false == UEServerConnect::GetInst().IsServer)
	//{

	//	SingleUpdate(DeltaTime);
	//}
	//else
	//{
	//	//LOG(L"ServerUpdate!!!!!!!");
	//	ServerUpdate(DeltaTime);
	//}
}

void ACharacter_Shinbi::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &ACharacter_Shinbi::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &ACharacter_Shinbi::MoveSide);
}

void ACharacter_Shinbi::ServerUpdate(float DeltaTime)
{
	ACharacterMaster::ServerUpdate(DeltaTime);

	//LOG(L"ShinbiUpdate");
}

void ACharacter_Shinbi::SingleUpdate(float DeltaTime)
{

}

//이동은 지금은 키보드이지만 추후에 마우스클릭으로 변경될수잇음
void ACharacter_Shinbi::MoveFront(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}

	//ACharacterMaster::MoveFront(_Scale);
	ShinbiAnim->MoveAnim();

	//LOG(TEXT("MoveFronSInbi"));
}
void ACharacter_Shinbi::MoveSide(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}

	//ACharacterMaster::MoveSide(_Scale);
	ShinbiAnim->MoveAnim();
	//LOG(TEXT("MoveSideSInbi"));
}

void ACharacter_Shinbi::RotationZ(float _Scale)
{
	//ACharacterMaster::RotationZ(_Scale);
	//LOG(TEXT("RotationZSInbi"));

}
