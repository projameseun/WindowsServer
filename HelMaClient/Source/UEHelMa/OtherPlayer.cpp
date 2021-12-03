// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherPlayer.h"
#include <LogicValue.h>
#include "UECharacterManager.h"
#include "KallariAnim.h"
#include "PhaseAnim.h"
#include "ShinbiAnim.h"

//#include "MainActor.h"

AOtherPlayer::AOtherPlayer()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> KalliAsset(L"SkeletalMesh'/Game/ParagonKallari/Characters/Heroes/Kallari/Skins/Rogue/Meshes/Kallari_Rogue.Kallari_Rogue'");

	if (KalliAsset.Succeeded())
	{
		KalliMesh = KalliAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ShinbiAsset(L"SkeletalMesh'/Game/ParagonShinbi/Characters/Heroes/Shinbi/Meshes/Shinbi.Shinbi'");

	if (KalliAsset.Succeeded())
	{
		ShinbiMesh = ShinbiAsset.Object;


	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PhaseAsset(L"SkeletalMesh'/Game/ParagonPhase/Characters/Heroes/Phase/Meshes/Phase_GDC.Phase_GDC'");

	if (KalliAsset.Succeeded())
	{
		PhaseMesh = PhaseAsset.Object;
	}

	//애니메이션 클래스 지정
	static ConstructorHelpers::FClassFinder<UPhaseAnim> PhaseAnimAsset(TEXT("AnimBlueprint'/Game/Player/BP_PhaseAnim.BP_PhaseAnim_C'"));

	if (PhaseAnimAsset.Succeeded())
	{
		//GetMesh()->SetAnimInstanceClass(PhaseAnimAsset.Class);

		PhaseClass = PhaseAnimAsset.Class;
	}
	
	static ConstructorHelpers::FClassFinder<UKallariAnim>	KalliAnimAsset(TEXT("AnimBlueprint'/Game/Player/BP_KallariAnim.BP_KallariAnim_C'"));

	if (KalliAnimAsset.Succeeded())
	{
		KallariClass = KalliAnimAsset.Class;
		
	}


	static ConstructorHelpers::FClassFinder<UShinbiAnim>	ShinbiAnimAsset(TEXT("AnimBlueprint'/Game/Player/BP_ShinbiAnim.BP_ShinbiAnim_C'"));

	if (ShinbiAnimAsset.Succeeded())
	{
		ShinbiClass = ShinbiAnimAsset.Class;
	}




	CharacterMesh.Add(KalliMesh);
	CharacterMesh.Add(ShinbiMesh);
	CharacterMesh.Add(PhaseMesh);

	CharacterAnim.Add(KallariClass);
	CharacterAnim.Add(ShinbiClass);
	CharacterAnim.Add(PhaseClass);

	
}


void AOtherPlayer::BeginPlay() 
{
	Super::BeginPlay();

	//여기서 애니메이션도 설정해줘야됨 
	//LOG(L"BeginOtherPlayer");

	ShinAnim = nullptr;
	PhaseAnim = nullptr;
	KallariAnim = nullptr;
	CharacterOtherName = UECharacterManager::GetInst().GetOtherName();
	CharacterName(CharacterOtherName);
}


void AOtherPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OtherPlayerUpdate(DeltaTime);
}

//Unregisters from NetworkPrediction System
void AOtherPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ActorEnd();
}


void AOtherPlayer::ActorEnd()
{
	UE_LOG(LogTemp, Error, TEXT("Player Death"));

	//클라이언트 때였기 때문에
   /*UEActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::MONSTER, reinterpret_cast<__int64>(this));*/
	//UpdateID 싱글이라면 이 ID를 자기 껄로 하면 되
   //UEActorManager::GetInst().EraseServerManagerObject((int)LogicValue::CollisionLayer::PLAYER, UpdateID);
}

void AOtherPlayer::OtherPlayerUpdate(float _DeltaTime)
{
	if (true == m_UpdateQueue.empty())
	{
		return;
	}

	const FTransform& Trans = GetActorTransform();
	FRotator RRot = Trans.Rotator();

	ActorUpdateData& Data = m_UpdateQueue.front();

	if (true == Data.IsSet)
	{
	/*	UE_LOG(LogTemp, Error, L"SetUpdate %f, %f, %f  Rot : %f", Data.Pos.x, Data.Pos.y, Data.Pos.z, Data.Rot.x);
		FRotator NewRRot;
		NewRRot.Add(0.0f, Data.Rot.x, 0.0f);
		SetActorRotation(NewRRot);

		FVector MoveVector = { Data.Pos.x, Data.Pos.y, 90.f };
		SetActorLocation(MoveVector);*/
		m_UpdateQueue.pop();
		return;
	}

	// UE_LOG(LogTemp, Error, L"OtherActor Update Fire %d, %d", (int)Data.CreateUpdateID.size(), Data.SubType);

	// 뭔가 만들게 있다는 소리죠?
	/*if (0 != Data.CreateUpdateID.size() && 1 == Data.SubType)
	{
		FVector Dir = { Data.Dir.x, Data.Dir.y, Data.Dir.z };
		FVector StartBulletPos = GetActorLocation() + Dir * 50.0f;
		ABullet* NewBullet = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABullet>(AMainActor::GetInst().m_BulletCreateType
			, StartBulletPos, (int)LogicValue::CollisionLayer::PLAYERBULLET, Data.CreateUpdateID[0], { 50.0f, 50.0f, 50.0f }, COLTYPE::CT_SPHERE);
		if (nullptr != NewBullet)
		{
			NewBullet->DirVector = Dir;
		}
	}
	else if (0 != Data.CreateUpdateID.size() && 3 == Data.SubType)
	{
		float4 ServerDir[3];
		ServerDir[0] = Data.Dir;
		ServerDir[1] = Data.Dir + Data.Right;
		ServerDir[2] = Data.Dir + -Data.Right;

		UE_LOG(LogTemp, Error, L"OtherActor Update Fire %f, %f %f", Data.Right.x, Data.Right.y, Data.Right.z);

		for (int i = 0; i < 3; i++)
		{
			ServerDir[i].Normalize();
		}

		FVector Dir[3];
		Dir[0] = { ServerDir[0].x, ServerDir[0].y, ServerDir[0].z };
		Dir[1] = { ServerDir[1].x, ServerDir[1].y, ServerDir[1].z };
		Dir[2] = { ServerDir[2].x, ServerDir[2].y, ServerDir[2].z };

		for (size_t i = 0; i < 3; i++)
		{
			FVector StartBulletPos = GetActorLocation() + Dir[i] * 50.0f;
			ABullet* NewBullet = UnActorManager::GetInst().CreateServerManagerObjectToCol<ABullet>(AMainActor::GetInst().m_BulletCreateType
				, StartBulletPos, (int)LogicValue::CollisionLayer::PLAYERBULLET, Data.CreateUpdateID[i], { 50.0f, 50.0f, 50.0f }, COLTYPE::CT_SPHERE);
			if (nullptr != NewBullet)
			{
				NewBullet->DirVector = Dir[i];
			}
		}
	}
	else if (0 != Data.CreateUpdateID.size() && 2 == Data.SubType)
	{
		FVector Dir = { Data.Dir.x, Data.Dir.y, Data.Dir.z };
		FVector StartBulletPos = GetActorLocation() + Dir * 50.0f;
		AExBullet* NewBullet = UnActorManager::GetInst().CreateServerManagerObjectToCol<AExBullet>(AMainActor::GetInst().m_ExBulletCreateType
			, StartBulletPos, (int)LogicValue::CollisionLayer::PLAYERBULLET, Data.CreateUpdateID[0], { 50.0f, 50.0f, 50.0f }, COLTYPE::CT_SPHERE);
		if (nullptr != NewBullet)
		{
			NewBullet->DirVector = Dir;
		}
	}*/



	if (Data.Rot != float4::ZERO)
	{

		LOG(L"Rotation : %f", Data.Rot.x);
		RRot.Add(0.0f, Data.Rot.x, 0.0f);
		SetActorRotation(RRot);
		
	}

	if (Data.Move != float4::ZERO)
	{
		UE_LOG(LogTemp, Error, L"Move OtherActor %f, %f, %f", Data.Move.x, Data.Move.y, Data.Move.z);
		FVector MoveVector = { Data.Move.x, Data.Move.y, Data.Move.z };
		SetActorLocation(GetActorLocation() + MoveVector);

		if (ShinAnim != nullptr)
		{
			ShinAnim->MoveAnim();
		}
		if (KallariAnim != nullptr)
		{
			KallariAnim->MoveAnim();
		}
		if (PhaseAnim != nullptr)
		{
			PhaseAnim->MoveAnim();
		}

	}

	m_UpdateQueue.pop();


}

void AOtherPlayer::CharacterName(const FString& _Name) 
{
	LOG(L"TestCharacterName");


	/*if (_Packet.CHARACTERNAME == L"Kallari")
	{
		LOG(L"KallariStart");

		ACharacter_Kallari::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY),0 });

		UECharacterManager::GetInst().CharacterManagerInit(&ACharacter_Kallari::GetInst(), _World);
	}

	else if (_Packet.CHARACTERNAME == L"Phase")
	{
		LOG(L"PhaseStart");
		ACharacter_Phase::GetInst().SetActorLocation({ static_cast<float>(_Packet.LastX), static_cast<float>(_Packet.LastY),0 });
		UECharacterManager::GetInst().CharacterManagerInit(&ACharacter_Phase::GetInst(), _World);
	}
	else if (_Packet.CHARACTERNAME == L"Shinbi")
	{
		LOG(L"ShinbiStart");*/

	//virtual void SetSkeletalMesh(class USkeletalMesh* NewMesh, bool bReinitPose = true) override;

	

	if (_Name == L"Kallari")
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh[0]);
		GetMesh()->SetAnimInstanceClass(CharacterAnim[0]);


		KallariAnim =Cast<UKallariAnim>(GetMesh()->GetAnimInstance());


	}
	else if (_Name == L"Shinbi")
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh[1]);
		GetMesh()->SetAnimInstanceClass(CharacterAnim[1]);
		ShinAnim = Cast<UShinbiAnim>(GetMesh()->GetAnimInstance());
	}
	else if (_Name == L"Phase")
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh[2]);
		GetMesh()->SetAnimInstanceClass(CharacterAnim[2]);
		PhaseAnim = Cast<UPhaseAnim>(GetMesh()->GetAnimInstance());
	}



	
}