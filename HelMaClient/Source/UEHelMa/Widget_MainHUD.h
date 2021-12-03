// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API UWidget_MainHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidget_CharacterState* Widget_CharacterState;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UUCharacter_SkillWidget* UCharacterSkillWidget;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UUBoss_StateWidget* UBossStateWidget;

protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetPlayerHP(float fPercent);
	void SetPlayerST(float fPercent);
	void SetPlayerName(const FString& strName);
	
};
