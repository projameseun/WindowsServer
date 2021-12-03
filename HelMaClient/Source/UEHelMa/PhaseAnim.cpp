// Fill out your copyright notice in the Description page of Project Settings.


#include "PhaseAnim.h"
#include "Character_Phase.h"
#include "OtherPlayer.h"

UPhaseAnim::UPhaseAnim()
{
	MoveStop = true;

	bStartRun = false;


	Dir = (uint8)EDirAnim::Front;

	bLevelStart = false;


}

void UPhaseAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AnimType = (uint8)EPhaseAnim::LevelStart;
}
void UPhaseAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//ACharacter_Phase* pOwner = Cast<ACharacter_Phase>(TryGetPawnOwner());


	//if (IsValid(pOwner))
	//{
	//	//Movemnet
	//	UCharacterMovementComponent* pMovement = pOwner->GetCharacterMovement();

	//	if (IsValid(pMovement))
	//	{
	//		IsGround = pMovement->IsMovingOnGround();


	//		//¶¥À» O
	//		if (IsGround)
	//		{

	//			//Powner->SetFalying(false);
	//			if (0.f < pMovement->Velocity.Size())
	//			{
	//				MoveStop = false;
	//				AnimType = (uint8)EPhaseAnim::Run;
	//				//SetPlayerReturnRun(true);

	//			}

	//			else
	//			{
	//				MoveStop = true;
	//				//SetPlayerReturnRun(false);

	//			}
	//		}

	//		//¶¥À» x ÇÏ´ÃÀ»³¯°íÀÕÀ»´ë
	//		else
	//		{

	//			//pOwner->SetFalying(true);

	//			//UE_LOG(LogTemp, Error, TEXT("Jumping!!!"));
	//		}
	//	}

	//}



}

void UPhaseAnim::MoveAnim()
{
	AnimType = (uint8)EPhaseAnim::Run;
}


//³ëÆ¼ÇÔ¼ö
void UPhaseAnim::AnimNotify_ReturnIdle()
{
	AnimType = (uint8)EPhaseAnim::Idle;
}


