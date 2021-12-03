// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectGameMode.h"
#include "Select_Controller.h"
#include "Pawn_SelectPlayer.h"
#include "Widget_Select.h"

ASelectGameMode::ASelectGameMode()
{
	DefaultPawnClass = APawn_SelectPlayer::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> SelectClass = TEXT("WidgetBlueprint'/Game/UI/BP_SelectWidget.BP_SelectWidget_C'");

	if (SelectClass.Succeeded())
	{
		SelectWidgetClass = SelectClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ASelect_Controller>	ControllerClass(TEXT("Blueprint'/Game/Player/BPSelect_Controller.BPSelect_Controller_C'"));

	if (ControllerClass.Succeeded())
	{

		PlayerControllerClass = ControllerClass.Class;
	}
}

void ASelectGameMode::BeginPlay()
{
	Super::BeginPlay();

	////테스

	//여기서 위젯생성 
	if (IsValid(SelectWidgetClass))
	{

		SelectWidget = Cast<UWidget_Select>(CreateWidget(GetWorld(), SelectWidgetClass));

		if (SelectWidget)
		{
			SelectWidget->AddToViewport();
		}
	}

	



}