// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SelectAnim.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class ESelectAnim : uint8
{
	Idle,
	Select
};

UCLASS()
class UEHELMA_API USelectAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	USelectAnim();
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "ESelectAnim"))
		uint8	AnimType;

public:
	virtual void NativeInitializeAnimation();

public:
	void ChangeAnim(ESelectAnim eAnim);

public:
	UFUNCTION()
		void AnimNotify_SelectEnd();
};
