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

	//�޸��Ⱑ ���࿡ 3������ ����� �ȴٸ� �ʿ��ҰŴ� �������ʿ����
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
	//�ִϸ��̼� ó�������Ҷ� 
	void NativeInitializeAnimation() override;
	//Tick
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION()
	void AnimNotify_ReturnIdle();

public:
	void MoveAnim();
	
};
