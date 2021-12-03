// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Animation/AnimInstance.h"
#include "KallariAnim.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EKallariAnim : uint8
{
	LevelStart,
	Idle,
	Run,
	Attack,
	Cast
};

/**
 * 
 */
UCLASS()
class UEHELMA_API UKallariAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UKallariAnim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EKallariAnim"))
	uint8 AnimType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EDirAnim"))
	uint8 Dir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool MoveStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool IsGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool bStartRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool bLevelStart;



public:
	void SetMoveDir(EDirAnim _Dir)
	{
		Dir = (uint8)_Dir;
	}

	//달리기가 만약에 3가지의 모션이 된다면 필요할거다 지금은필요없음
	//void SetPlayerReturnRun(bool _Run)
	//{
	//	
	//	bStartRun = _Run;
	//}

	/*bool GetPlayerStartRun()
	{
		return bStartRun;
	}*/



public:
	//애니메이션 처음시작할때 
	void NativeInitializeAnimation() override;
	//Tick
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION()
	void AnimNotify_ReturnIdle();

public:
	void MoveAnim();
	
};
