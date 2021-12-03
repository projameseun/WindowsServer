// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariAnim.h"
#include "Character_Kallari.h"
#include "OtherPlayer.h"
//#include "Other_Kallari.h"

UKallariAnim::UKallariAnim()
{
	MoveStop = true;

	bStartRun = false;


	Dir = (uint8)EDirAnim::Front;

	bLevelStart = false;


}

void UKallariAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AnimType = (uint8)EKallariAnim::LevelStart;
}
void UKallariAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);



}

void UKallariAnim::MoveAnim()
{
	AnimType = (uint8)EKallariAnim::Run;
}

//노티함수
void UKallariAnim::AnimNotify_ReturnIdle()
{
	AnimType = (uint8)EKallariAnim::Idle;
}

