// Fill out your copyright notice in the Description page of Project Settings.


#include "StartGameMode.h"
#include "Widget_Start.h"

AStartGameMode::AStartGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> StartClass = TEXT("WidgetBlueprint'/Game/UI/BP_StartWidget.BP_StartWidget_C'");

	if (StartClass.Succeeded())
	{
		StartWidgetClass = StartClass.Class;
	}


}

void AStartGameMode::BeginPlay()
{
	Super::BeginPlay();

	////테스

	//여기서 위젯생성 
	if (IsValid(StartWidgetClass))
	{
		
		StartWidget = Cast<UWidget_Start>(CreateWidget(GetWorld(), StartWidgetClass));

		if (StartWidget)
		{
			StartWidget->AddToViewport();
		}
	}



}