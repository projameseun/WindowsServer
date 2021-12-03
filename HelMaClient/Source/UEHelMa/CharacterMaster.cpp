// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMaster.h"
#include "UECharacterManager.h"
#include <ClientToServer.h>
#include "UEServerConnect.h"


ACharacterMaster* ACharacterMaster::MasterCharacter = nullptr;

// Sets default values
ACharacterMaster::ACharacterMaster() :fSpeed(1.f), RotSpeed(150.0f) , MoveVector(0,0,0),MoveRot(0,0,0) ,IsMouseCenter(false)
{

	PrimaryActorTick.bCanEverTick = true;

	//카메라,매쉬등 무조건 생성자에서 만들어줘야된다.

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Arm = CreateDefaultSubobject<USpringArmComponent>("Arm");

	//카메라가 플레이어를 따라가게 만든다.
	Arm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(Arm);

	//OtherPlayerTsub로 불러오기
	//Blueprint'/Game/Player/BP_OtherPlayer.BP_OtherPlayer'
	static ConstructorHelpers::FClassFinder<AOtherPlayer> OtherPlayerAsset(TEXT("Blueprint'/Game/OtherPlayer/BP_OtherPlayer.BP_OtherPlayer_C'"));

	if (OtherPlayerAsset.Succeeded())
	{
		m_OtherPlayerCreateType = OtherPlayerAsset.Class;
	}
}

ACharacterMaster::~ACharacterMaster()
{
	//UnResManager::Inst().Release();
	//UnActorManager::GetInst().Clear();
	//UnServerConnect::GetInst().Close();
	//UnServerConnect::GetInst().ThreadStop();
}

// Called when the game starts or when spawned
void ACharacterMaster::BeginPlay()
{
	Super::BeginPlay();
	MasterCharacter = this;
	

	
	fSpeed = GetCharacterMovement()->MaxWalkSpeed;

	//콜리전링크
	
}

// Called every frame
void ACharacterMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UECharacterManager::GetInst().DestoryRelease();
	UEServerConnect::GetInst().MainProcess.MsgUpdate();


	if (0 == UEServerConnect::GetInst().m_GameStart)
	{
		LOGERROR(L"NotLogin!!");
		return;
	}

	MousePosCenterLock(UGameplayStatics::GetPlayerController(this, 0));


	if (false == UEServerConnect::GetInst().IsServer)
	{
		
		SingleUpdate(DeltaTime);
	}
	else
	{
		//LOG(L"ServerUpdate!!!!!!!");
		ServerUpdate(DeltaTime);
	}
	

}

// Called to bind functionality to input
void ACharacterMaster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("MouseFree"),EInputEvent::IE_Pressed ,this, &ACharacterMaster::MouseFree);

	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &ACharacterMaster::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &ACharacterMaster::MoveSide);
	//PlayerInputComponent->BindAxis(TEXT("RotationZ"), this, &ACharacterMaster::RotationZ);

}

void ACharacterMaster::ServerUpdate(float DeltaTime)
{
	//LOG(L"ServerUpdate!!!");
	//콜리전은 모든캐릭터들이 받는다

	if (false == IsMouseCenter)
	{
		return;
	}



	const FTransform& Trans = GetActorTransform();
	FVector2D RotScale = MouseCenter - MousePos;
	float RotX = -RotScale.X * DeltaTime * RotSpeed;
				
	MoveVector.Normalize();
	FVector CalMoveVector = MoveVector * DeltaTime * fSpeed;

	FRotator RRot = Trans.Rotator();

	if (CalMoveVector != FVector(0, 0, 0))
	{
		
		FVector4 CalPos = Trans.GetLocation()+ CalMoveVector;
		SetActorLocation(CalPos);
		
	}

	// 회전
	if (true == IsMouseCenter && RotX != 0.0f)
	{
		LOG(L"RotX : %f", RotX);
		RRot.Add(0.0f, RotX, 0.0f);
		SetActorRotation(RRot);
	}
	else if (RotX == 0.f)
	{
		//LOG(L"RotXZero : %f", RotX);
	}
	
	if (MoveVector != FVector(0, 0, 0) || RotX != 0.f) // 이동했을때)
	{
		

		//움직일때마다 서버로 패킷을보냅니다
		ClientPlayerPacket NewMovePacekt;
		NewMovePacekt.m_State = ActorState::Update;
		NewMovePacekt.ActorData.DeltaTime = DeltaTime;
		NewMovePacekt.ActorData.Rot = { RotX, RotScale.Y };
		NewMovePacekt.ActorData.Pos = { GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z };
		NewMovePacekt.ActorData.Dir = { GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z };
		NewMovePacekt.ActorData.Right = { GetActorRightVector().X, GetActorRightVector().Y, GetActorRightVector().Z };
		NewMovePacekt.ActorData.Move = { CalMoveVector.X, CalMoveVector.Y, CalMoveVector.Z };
		NewMovePacekt.ActorData.Scale = { GetActorScale().X,GetActorScale().Y,GetActorScale().Z };
	
		//
		UEServerConnect::GetInst().Send(NewMovePacekt);
	}

	if (MoveVector != FVector(0, 0, 0) || RotScale != FVector2D(0, 0))
	{
		MoveVector = FVector(0, 0, 0);
		RotScale = FVector2D(0, 0);
	}


	
}


void ACharacterMaster::SingleUpdate(float DeltaTime)
{
	

}

void ACharacterMaster::MouseFree()
{
	IsMouseCenter = !IsMouseCenter;

	MoveVector = FVector(0.0F, 0.0F, 0.0F);
	MousePos = FVector2D(0.0F, 0.0F);
}

void ACharacterMaster::MoveFront(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}

	if (_Scale == 1.f)
	{
		MoveVector += GetActorForwardVector();
	}
	else if (_Scale == -1.f)
	{
		MoveVector -= GetActorForwardVector();
	}

	//AddMovementInput(GetActorForwardVector(), _Scale);
	


	//만약에 이동이 오른쪽왼쪽 뒤가 존재한다면 쓸거임 지금은안씀
	/*if (IsValid(KallariAnim))
	{
		if (0.f < _Scale)
		{
			KallariAnim->SetMoveDir(EDirAnim::Front);
		}
		else if (0.f > _Scale)
		{
			KallariAnim->SetMoveDir(EDirAnim::Back);
		}

	}*/
}

void ACharacterMaster::MoveSide(float _Scale)
{
	if (_Scale == 0.f)
	{
		return;
	}

	if (_Scale == 1.f)
	{
		MoveVector += GetActorRightVector();
	}
	else if (_Scale == -1.f)
	{
		MoveVector -= GetActorRightVector();
	}

	//AddMovementInput(GetActorRightVector(), _Scale);


	/*if (IsValid(KallariAnim))
	{
		if (0.f < _Scale)
		{
			KallariAnim->SetMoveDir(EDirAnim::Front);
		}
		else if (0.f > _Scale)
		{
			KallariAnim->SetMoveDir(EDirAnim::Back);
		}

	}*/
}

void ACharacterMaster::RotationZ(float _Scale)
{	
	/*if (_Scale == 1.f)
	{
		MoveRot += GetActorRotation();
	}
	else if (_Scale == -1.f)
	{
		MoveRot -= GetActorRotation();
	}

	AddControllerYawInput(_Scale);*/
}

void ACharacterMaster::MousePosCenterLock(APlayerController* _Con)
{
	if (false == IsMouseCenter)
	{
		return;
	}


	if (nullptr != _Con)
	{
		const ULocalPlayer* LPlayer = _Con->GetLocalPlayer();
		if (nullptr != LPlayer && nullptr != LPlayer->ViewportClient)
		{
			FViewport* ViewPtr = LPlayer->ViewportClient->Viewport;

			LPlayer->ViewportClient->GetMousePosition(MousePos);

			if (nullptr != ViewPtr)
			{
				LPlayer->ViewportClient->GetViewportSize(MouseCenter);
				//UE_LOG(LogTemp, Error, L"MousePos %f %f", MousePos.X, MousePos.Y);
				//UE_LOG(LogTemp, Error, L"ScreenSize %f %f", MouseCenter.X, MouseCenter.Y);
				const int32 X = static_cast<int32>(MouseCenter.X * 0.5f);
				const int32 Y = static_cast<int32>(MouseCenter.Y * 0.5f);
				ViewPtr->SetMouse(X, Y);
				MouseCenter.X = X;
				MouseCenter.Y = Y;
			}

		}

	}
}