#pragma once
#include "PacketUpdater.h"


class ServerToClientPacketUpdater : public PacketUpdater
{
public:
    STOCPACKETSTATIC(AccountResultPacket)
    STOCPACKETSTATIC(LoginResultPacket)
    STOCPACKETSTATIC(CharacterPacket)
    STOCPACKETSTATIC(CharacterUpdatePacket)
    STOCPACKETSTATIC(SelectUpdatePacket)
    STOCPACKETSTATIC(GameStartPacket)
    STOCPACKETSTATIC(PlayerUpdatePacket)
    STOCPACKETSTATIC(PlayerUpdateDataPacket)
    STOCPACKETSTATIC(MonsterUpdatePacket)
    STOCPACKETSTATIC(MonsterUpdateDataPacket)
    STOCPACKETSTATIC(ItemUpdatePacket)
    STOCPACKETSTATIC(WorldMoveOKPacket)
    STOCPACKETSTATIC(RankPacket)
    STOCPACKETSTATIC(PlayerDeathPacket)

public:
    const char* Update()
    {
        // � ��Ŷ���� ������ �ǰ�.
        PacketInit();

        switch (m_STOCType)
        {
            STOCCASE(AccountResultPacket)
            STOCCASE(LoginResultPacket)
            STOCCASE(CharacterPacket)
            STOCCASE(CharacterUpdatePacket)
            STOCCASE(SelectUpdatePacket)
            STOCCASE(GameStartPacket)
            STOCCASE(PlayerUpdateDataPacket)
            STOCCASE(PlayerUpdatePacket)
            STOCCASE(MonsterUpdatePacket)
            STOCCASE(MonsterUpdateDataPacket)
            STOCCASE(ItemUpdatePacket)
            STOCCASE(WorldMoveOKPacket)
            STOCCASE(RankPacket)
            STOCCASE(PlayerDeathPacket)
        case SERVERTOCLIENTTYPE::MAX:
        default:
            break;
        }
        return "ERROR";
    }

public:
    ServerToClientPacketUpdater(char* _Ptr, size_t _Size) : PacketUpdater(_Ptr, _Size)
    {
    }

    virtual ~ServerToClientPacketUpdater() 
    {
    }

};

