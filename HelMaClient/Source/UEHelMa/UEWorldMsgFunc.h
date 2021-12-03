// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"

/**
 * 
 */
class CharacterPacket;
class CharacterUpdatePacket;
class SelectUpdatePacket;
class PlayerUpdateData;
class PlayerUpdateDataPacket;
class PlayerDeathPacket;

class UEHELMA_API UEWorldMsgFunc
{
public:
	static void SelectCreate(UWorld* _World, SelectUpdatePacket _Packet);
	static void PlayerCreate(UWorld* _World, CharacterPacket _Packet);
	static void WaitPlayerCreate(UWorld* _World, PlayerUpdateDataPacket Data);
	static void WaitPlayerInWorld(UWorld* _World, PlayerUpdateDataPacket Data);

	static void UpdatePlayer(UWorld* _World, PlayerUpdateDataPacket Data);
	static void DeathPlayer(UWorld* _World, PlayerUpdateDataPacket Data);

	static void LogOut(UWorld* _World, PlayerDeathPacket _Packet);

public:
	UEWorldMsgFunc();
	virtual ~UEWorldMsgFunc() = 0;
};
