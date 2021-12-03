// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Widget_CharacterImg.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API UWidget_CharacterImg : public UUserWidget
{
	GENERATED_BODY()

protected:
	UImage* m_Image;

protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetCharacterImg(int _Index);
	void InitCharacterImg();
};
