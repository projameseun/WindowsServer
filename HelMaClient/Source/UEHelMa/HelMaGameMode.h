// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "HelMaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API AHelMaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHelMaGameMode();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget>	MainWidgetClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidget_MainHUD* MainHUDWidget;

public:
	class UWidget_MainHUD* GetMainWidget()	const
	{
		return MainHUDWidget;
	}

public:
	virtual void BeginPlay();
	
};
