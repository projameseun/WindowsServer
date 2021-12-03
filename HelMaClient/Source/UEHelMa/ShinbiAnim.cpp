// Fill out your copyright notice in the Description page of Project Settings.


#include "ShinbiAnim.h"
#include "Character_Shinbi.h"
#include "OtherPlayer.h"

UShinbiAnim::UShinbiAnim()
{
	MoveStop = true;

	bStartRun = false;


	Dir = (uint8)EDirAnim::Front;

	bLevelStart = false;


}

void UShinbiAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AnimType = (uint8)EShinbiAnim::LevelStart;
}
void UShinbiAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//ACharacter_Shinbi* pOwner = Cast<ACharacter_Shinbi>(TryGetPawnOwner());
	//

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
	//				AnimType = (uint8)EShinbiAnim::Run;
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

//³ëÆ¼ÇÔ¼ö
void UShinbiAnim::AnimNotify_ReturnIdle()
{
	AnimType = (uint8)EShinbiAnim::Idle;
}

void UShinbiAnim::MoveAnim()
{
	AnimType = (uint8)EShinbiAnim::Run;	
}