#pragma once
#include "ServerPlayer.h"
#include <ServerConnecter.h>
#include <ClientToServer.h>

class World;
class WorldMsgFunc
{
public:
    static void SelectPlayerCreate(World* _World, ServerConnecter* _Connecter);
    static void WaitPlayerCreate(World* _World, ServerConnecter* _Connecter);
    static void WaitPlayerInWorld(World* _World, ServerConnecter* _Connecter);
    static void PlayerUpdate(World* _World, ServerConnecter* _Connecter, ClientPlayerPacket _Packet);
    static void PlayerDeath(World* _World, __int64 _ID);

    static void MonsterUpdate(World* _World, MonsterUpdateDataPacket _Packet);
    static void MonsterDeath(World* _World, MonsterUpdateDataPacket _MonsterData);

    static void ItemUpdate(World* _World, ItemUpdateData _Packet);
    static void ItemDeath(World* _World, ItemUpdateData _Packet);

    static void WorldMoveOk(World* _World, ServerConnecter* _Connect);
};

