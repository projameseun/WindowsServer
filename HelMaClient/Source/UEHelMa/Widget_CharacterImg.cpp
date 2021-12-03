// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_CharacterImg.h"
#include "UEResManager.h"



void UWidget_CharacterImg::NativePreConstruct()
{
	Super::NativePreConstruct();
 }
void UWidget_CharacterImg::NativeConstruct()
{
	Super::NativeConstruct();

	m_Image = Cast<UImage>(GetWidgetFromName("CharacterImg"));

	if (nullptr == m_Image)
	{
		UE_LOG(LogTemp, Error, TEXT("if (nullptr == m_Image)"));
	}
	
 }
void UWidget_CharacterImg::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UWidget_CharacterImg::SetCharacterImg(int _Index)
{


	UTexture2D* SetTex = UEResManager::Inst().GetIconImage(_Index);

	if (nullptr == SetTex)
	{
		UE_LOG(LogTemp, Error, TEXT("void UInvenIcon::SetIcon(int _Index)  if (nullptr == SetTex) %d"), _Index);
		return;
	}

	m_Image->SetBrushFromTexture(SetTex);
}

void UWidget_CharacterImg::InitCharacterImg()
{
	UTexture2D* SetTex = nullptr;

	
	m_Image->SetBrushFromTexture(SetTex);
}

