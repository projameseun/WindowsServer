// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "SelectGameMode.generated.h"

/**
 여기는 이미 서버가 접속이 된상태고 로그인이 된상태이다 
 그리고 여기서는 캐릭터를 선택할수잇고 아니면 기존캐릭터를 고를수잇고 그걸실행하는 기능
 일단은 그냥 버튼으로 게임시작만 해놀거고 추후에 추가 
 */
UCLASS()
class UEHELMA_API ASelectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASelectGameMode();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget>	SelectWidgetClass;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UWidget_Select* SelectWidget;

public:
	class UWidget_Select* GetMainWidget()	const
	{
		return SelectWidget;
	}

public:
	virtual void BeginPlay();
	
};
