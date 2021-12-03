// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Select.generated.h"

/**
 * 
 */

UCLASS()
class UEHELMA_API UWidget_Select : public UUserWidget
{
	GENERATED_BODY()



public:
	static UWidget_Select* SelectWidgetInst;

public:
	static int32 DataSize;


protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* StartButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* DeleteButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* CreateButton0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* CreateButton1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* CreateButton2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* CreateButton3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* MainCreateButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* BackButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* SelectMainImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* MainLevelImage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* m_NoNickName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* m_MainLevelText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidget_CharacterImg* CharacterImg_Widget0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidget_CharacterImg* CharacterImg_Widget1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidget_CharacterImg* CharacterImg_Widget2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidget_CharacterImg* CharacterImg_Widget3;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString CreateString;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	 FString CreateString1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	 FString CreateString2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString CreateString3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_NickName;


	//NoNickName

	FText* m_CharacterName;

	float fTime;
	bool bTime;

	bool bLevel;
	float fMainLevelTime;
	


public:
	FText* SetCharacterName(FText* _Name)
	{
		return m_CharacterName = _Name;
	}

	UWidget_CharacterImg* GetCharacterImg0()
	{
		return CharacterImg_Widget0;
	}

	UWidget_CharacterImg* GetCharacterImg1()
	{
		return CharacterImg_Widget1;
	}

	UWidget_CharacterImg* GetCharacterImg2()
	{
		return CharacterImg_Widget2;
	}

	UWidget_CharacterImg* GetCharacterImg3()
	{
		return CharacterImg_Widget3;
	}

	 void SetCreateString(FString _Name)
	{
		 CreateString = _Name;
	}

	void SetCreateString1(FString _Name)
	{
		CreateString1 = _Name;

	}

	void SetCreateString2(FString _Name)
	{
		CreateString2 = _Name;
	}

	void  SetCreateString3(FString _Name)
	{
		CreateString3 = _Name;
	}

private:

	void NotNickNameTime();


private:
	UFUNCTION(BlueprintCallable)
	void GameStartCallback();

	UFUNCTION(BlueprintCallable)
	void GameDelteCallback();

	UFUNCTION(BlueprintCallable)
	void GameEndButtonCallback();

	//CreateaButton
	UFUNCTION(BlueprintCallable)
	void CreateButtonCallback0();
	
	UFUNCTION(BlueprintCallable)
	void CreateButtonCallback1();
	
	UFUNCTION(BlueprintCallable)
	void CreateButtonCallback2();
	
	UFUNCTION(BlueprintCallable)
	void CreateButtonCallback3();
	
	UFUNCTION(BlueprintCallable)
	void BackButtonCallBack();

	UFUNCTION(BlueprintCallable)
	void MainCreateButtonCallback();


public:
	void StartButtonEnable(bool bEnable);


	//캐릭터생성 스타트를 뺀나머지 버튼이 다꺼진다
	void HiddenMainStart();
	void VisibleMainStart();

	void VisibleCharacterWidgetImg0();
	void VisibleCharacterWidgetImg1();
	void VisibleCharacterWidgetImg2();
	void VisibleCharacterWidgetImg3();

	void HiddentCharacterWidgetImg();

	void StartOpenLevelTime();

	
	
};
