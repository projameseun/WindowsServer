// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"

/**
 * 
 */
class UEHELMA_API UEResManager
{
public:
	static UEResManager& Inst()
	{
		static UEResManager NewInst;
		return NewInst;
	}

private:
	TArray<UTexture2D*> m_CharacterImgArray;

public:
	UTexture2D* GetIconImage(int _Index);

public:
	void ResInit();
	void Release();

public:
	UEResManager();
	~UEResManager();
};
