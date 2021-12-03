// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"

/**
 * 
 */
class AccountResultPacket;
class LoginResultPacket;
class CharacterPacket;
class CharacterUpdatePacket;
class SelectUpdatePacket;
class GameStartPacket;
class PlayerUpdatePacket;
class MonsterUpdatePacket;
class ItemUpdatePacket;
class WorldMoveOKPacket;
class RankPacket;
class PlayerUpdateDataPacket;
class MonsterUpdateDataPacket;
class PlayerDeathPacket;


class UEHELMA_API ClientPacketFunc
{
public: // Static Func
    static void Init();
    static void AccountResultPacketProcess(AccountResultPacket       _Packet);
    static void LoginResultPacketProcess(LoginResultPacket         _Packet);
    static void CharacterPacketProcess(CharacterPacket           _Packet);
    static void CharacterUpdatePacketProcess(CharacterUpdatePacket           _Packet);
    static void SelectUpdatePacketProcess(SelectUpdatePacket           _Packet);
    static void GameStartPacketProcess(GameStartPacket           _Packet);
    static void PlayerUpdatePacketProcess(PlayerUpdatePacket        _Packet);
    static void PlayerUpdateDataPacketProcess(PlayerUpdateDataPacket        _Packet);
    static void MonsterUpdatePacketProcess(MonsterUpdatePacket       _Packet);
    static void MonsterUpdateDataPacketProcess(MonsterUpdateDataPacket       _Packet);
    static void ItemUpdatePacketProcess(ItemUpdatePacket           _Packet);
    static void WorldMoveOKPacketProcess(WorldMoveOKPacket _Packet);
    static void RankPacketProcess(RankPacket _Packet);
    static void PlayerDeathPacketProcess(PlayerDeathPacket _Packet);

public:
	ClientPacketFunc();
	~ClientPacketFunc();
};
