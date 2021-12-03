// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
//#include "EngineGlobals.h"
//#include "DestructibleComponent.h"
//#include "Engine.h"
//#include "Engine/AssetManager.h"
//#include "Runtime/Engine/Classes/Engine/GameEngine.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"
//#include "NavigationSystem/Public/NavigationPath.h"
//#include "Engine/DataTable.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class ECharacterName : uint8
{
	Kallari,
	Phase,
	Shinbi,
	MAX
};


UENUM(BlueprintType, Meta = (Bitflags))
enum class EDirAnim : uint8
{
	Front,
	Back,
	Right,
	Left
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EMonsterAnim : uint8
{
	Idle,
	Run,
	Attack,
	Hit,
	Death
};


DECLARE_LOG_CATEGORY_EXTERN(UEHelMa, Log, All);
#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))
#define	LOGERROR(Format, ...)	UE_LOG(UEHelMa, Error, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define	LOG(Format, ...)	UE_LOG(UEHelMa, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

void PrintViewport(float fTime, const FColor& Color,
	const FString& strText);
