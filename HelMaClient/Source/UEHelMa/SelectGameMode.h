// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "SelectGameMode.generated.h"

/**
 ����� �̹� ������ ������ �Ȼ��°� �α����� �Ȼ����̴� 
 �׸��� ���⼭�� ĳ���͸� �����Ҽ��հ� �ƴϸ� ����ĳ���͸� �����հ� �װɽ����ϴ� ���
 �ϴ��� �׳� ��ư���� ���ӽ��۸� �س�Ű� ���Ŀ� �߰� 
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
