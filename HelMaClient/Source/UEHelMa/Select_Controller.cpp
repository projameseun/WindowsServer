// Fill out your copyright notice in the Description page of Project Settings.


#include "Select_Controller.h"
#include "Pawn_SelectPlayer.h"
#include "SelectAnim.h"
#include "SelectGameMode.h"
#include "Widget_Select.h"
#include "HelMaGameInstance.h"

ASelect_Controller::ASelect_Controller()
{
	bLButtonDown = false;
	bRButtonDown = false;

	bShowMouseCursor = true;

	bEnableClickEvents = false;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
}

void ASelect_Controller::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI	inputMode;
	SetInputMode(inputMode);

	InputPitchScale = 0.f;
	InputYawScale = 0.f;
	InputRollScale = 0.f;
}

void ASelect_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("LButton"), EInputEvent::IE_Pressed,
		this, &ASelect_Controller::LButtonClick);
	InputComponent->BindAction(TEXT("LButton"), EInputEvent::IE_Released,
		this, &ASelect_Controller::LButtonRelease);

	InputComponent->BindAction(TEXT("RButton"), EInputEvent::IE_Pressed,
		this, &ASelect_Controller::RButtonClick);
	InputComponent->BindAction(TEXT("RButton"), EInputEvent::IE_Released,
		this, &ASelect_Controller::RButtonRelease);
}

void ASelect_Controller::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bLButtonDown)
	{
		
		Picking();
		bLButtonDown = false;
	}

	if (bRButtonDown)
	{
		bRButtonDown = false;
	}
}

void ASelect_Controller::LButtonClick()
{
	bLButtonDown = true;
}

void ASelect_Controller::LButtonRelease()
{
	bLButtonDown = false;
}

void ASelect_Controller::RButtonClick()
{
	bRButtonDown = true;
}

void ASelect_Controller::RButtonRelease()
{
	bRButtonDown = false;
}

void ASelect_Controller::Picking()
{
	FHitResult	result;

	bool	bHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
		false, result);

	if (bHit)
	{

		APawn_SelectPlayer* SelectPlayer = Cast<APawn_SelectPlayer>(result.GetActor());

		if (IsValid(SelectPlayer))
		{
			LOG(L"SelectPlayer");
			USelectAnim* Anim = SelectPlayer->GetAnim();

			Anim->ChangeAnim(ESelectAnim::Select);

			ASelectGameMode* GameMode = Cast<ASelectGameMode>(GetWorld()->GetAuthGameMode());
			UWidget_Select* SelectWidget = GameMode->GetMainWidget();

			if (SelectPlayer->GetCharacterName() == TEXT("Kallari"))
			{
			
				LOG(L"Kallari");
				SelectWidget->StartButtonEnable(true);
				//캐릭터네임도 전달한다
		

				UHelMaGameInstance* GameInst = Cast<UHelMaGameInstance>(GetGameInstance());
				GameInst->SetSelectPlayerName(TEXT("Kallari"));
			}

			else if (SelectPlayer->GetCharacterName() == TEXT("Phase"))
			{
				SelectWidget->StartButtonEnable(true);

				UHelMaGameInstance* GameInst = Cast<UHelMaGameInstance>(GetGameInstance());
				GameInst->SetSelectPlayerName(TEXT("Phase"));

			}

			else if (SelectPlayer->GetCharacterName() == TEXT("Shinbi"))
			{
				SelectWidget->StartButtonEnable(true);

				UHelMaGameInstance* GameInst = Cast<UHelMaGameInstance>(GetGameInstance());
				GameInst->SetSelectPlayerName(TEXT("Shinbi"));
			}
		}
	}
}
