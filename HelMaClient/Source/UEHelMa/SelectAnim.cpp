// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectAnim.h"

USelectAnim::USelectAnim()
{
}

void USelectAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	AnimType = (uint8)ESelectAnim::Idle;
}

void USelectAnim::ChangeAnim(ESelectAnim eAnim)
{
	AnimType = (uint8)eAnim;
}

void USelectAnim::AnimNotify_SelectEnd()
{
	AnimType = (uint8)ESelectAnim::Idle;
}
