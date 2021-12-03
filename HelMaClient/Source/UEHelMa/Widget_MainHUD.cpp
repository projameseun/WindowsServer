// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_MainHUD.h"
#include "Widget_CharacterState.h"
#include "UEServerConnect.h"

void UWidget_MainHUD::NativePreConstruct()
{
	Super::NativePreConstruct();
	Widget_CharacterState = Cast<UWidget_CharacterState>(GetWidgetFromName(TEXT("BP_CharacterStateWidget")));
	

 }
void UWidget_MainHUD::NativeConstruct()
{
	Super::NativeConstruct();

 }
void UWidget_MainHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	
}

void UWidget_MainHUD::SetPlayerHP(float fPercent)
{
	Widget_CharacterState->SetHP(fPercent);
}
void UWidget_MainHUD::SetPlayerST(float fPercent)
{
	Widget_CharacterState->SetST(fPercent);
}
void UWidget_MainHUD::SetPlayerName(const FString& strName)
{
	//Widget_CharacterState->Se
}