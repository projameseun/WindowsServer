// Fill out your copyright notice in the Description page of Project Settings.


#include "HelMaGameMode.h"
#include "KallariController.h"
#include "Widget_MainHUD.h"


AHelMaGameMode::AHelMaGameMode()
{
	//static ConstructorHelpers::FClassFinder<ACharacter_Shinbi> PlayerClass = (TEXT("Blueprint'/Game/Player/BP_Shinbi.BP_Shinbi_C'"));

	//if (PlayerClass.Succeeded())
	//{
	//	DefaultPawnClass = PlayerClass.Class;
	//}

	static ConstructorHelpers::FClassFinder<UUserWidget> MainClass = TEXT("WidgetBlueprint'/Game/UI/BP_MainHUDWidget.BP_MainHUDWidget_C'");

	if (MainClass.Succeeded())
	{
		MainWidgetClass = MainClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AKallariController> ControllerClass = (TEXT("Blueprint'/Game/Player/BP_KallariController.BP_KallariController_C'"));

	if (ControllerClass.Succeeded())
	{
		PlayerControllerClass = ControllerClass.Class;
	}
}

 void AHelMaGameMode::BeginPlay()
{
	 Super::BeginPlay();

	 //Å×½º
	 

	 if (IsValid(MainWidgetClass))
	 {

		 MainHUDWidget = Cast<UWidget_MainHUD>(CreateWidget(GetWorld(), MainWidgetClass));

		 if (MainHUDWidget)
		 {
			 MainHUDWidget->AddToViewport();
		 }
	 }

}