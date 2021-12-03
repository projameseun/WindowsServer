// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "Select_Controller.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API ASelect_Controller : public APlayerController
{
	GENERATED_BODY()

public:
	ASelect_Controller();

private:
	bool	bLButtonDown;
	bool	bRButtonDown;

private:
	virtual void BeginPlay();
	virtual void SetupInputComponent();
	virtual void PlayerTick(float DeltaTime);

public:
	void LButtonClick();
	void LButtonRelease();
	void RButtonClick();
	void RButtonRelease();

private:
	void Picking();
	
};
