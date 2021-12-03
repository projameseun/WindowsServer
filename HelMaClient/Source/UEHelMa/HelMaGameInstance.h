// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "HelMaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEHELMA_API UHelMaGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	static UHelMaGameInstance* GameMode;

public:

	static UHelMaGameInstance& GetInst()
	{
		return *GameMode;
	}

public:
	UHelMaGameInstance();
	~UHelMaGameInstance();

	FString		SelectPlayerName;

public:
	void SetSelectPlayerName(const FString& PlayerName)
	{
		SelectPlayerName = PlayerName;

		int a = 0;
	}

	//UFUNCTION(BlueprintCallable)
	FString GetSelectPlayerName()	const
	{
		
		return SelectPlayerName;
	}

	UFUNCTION(BlueprintCallable)
	FString GetInstanceSelectPlayerName()	const
	{

		return GetInst().SelectPlayerName;
	}




protected:
	virtual void Init();
		
};
