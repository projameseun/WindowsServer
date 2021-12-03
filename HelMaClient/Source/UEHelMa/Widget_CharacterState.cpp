// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_CharacterState.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidget_CharacterState::NativeConstruct()
{
	Super::NativeConstruct();

	//NameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Hp_Bar")));
	StBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("St_Bar")));
}

void UWidget_CharacterState::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	
}

void UWidget_CharacterState::SetHP(float fPercent)
{
	HpBar->SetPercent(fPercent);
}

void UWidget_CharacterState::SetST(float fPercent)
{
	StBar->SetPercent(fPercent);
}

//void UUCharacterStateWidget::SetNameText(const FString& strText)
//{
//	NameText->SetText(FText::FromString(strText));
//}