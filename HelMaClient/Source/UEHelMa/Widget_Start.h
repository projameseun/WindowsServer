// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Start.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API UWidget_Start : public UUserWidget
{
	GENERATED_BODY()

public:
	static FString IPText;
	static FString IDText;
	static FString PASSText;


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FText m_IP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FText m_ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FText m_Password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class UTextBlock* m_LoginText;


	float fTime;
	bool bTime;

public:
	void NotLoginText();

protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

private:
	UFUNCTION(BlueprintCallable)
	void ConnectButtonCallback();

	UFUNCTION(BlueprintCallable)
	void LoginButtonCallback();

	UFUNCTION(BlueprintCallable)
	void SingleButtonCallback();

	UFUNCTION(BlueprintCallable)
	void AccountButtonCallback();

public:
	void IPSave();

	UFUNCTION(BlueprintCallable, Category = Attachment)
	void IPLoad();

	
};
