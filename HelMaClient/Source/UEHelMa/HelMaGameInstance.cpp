// Fill out your copyright notice in the Description page of Project Settings.


#include "HelMaGameInstance.h"
#include "UEResManager.h"
#include "UEServerConnect.h"
#include "UECharacterManager.h"

UHelMaGameInstance* UHelMaGameInstance::GameMode = nullptr;

UHelMaGameInstance::UHelMaGameInstance()
{

}

UHelMaGameInstance::~UHelMaGameInstance()
{
	UEResManager::Inst().Release();
	UECharacterManager::GetInst().Clear();
	UEServerConnect::GetInst().Close();
	UEServerConnect::GetInst().ThreadStop();
}


void UHelMaGameInstance::Init()
{
	GameMode = this;
	UEServerConnect::GetInst().Init(GetWorld());
	UEResManager::Inst().ResInit();

}