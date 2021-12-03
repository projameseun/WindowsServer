#pragma once

enum class PACKETTYPE : int
{
    ServerToClient,
    ClientToServer,
    ClientAndServer,
    MAX
};


enum class CLIENTTOSERVERTYPE : int
{
    LoginPacket, // �α���
    SelectCharacterPacket,   //�α��εǰ� ĳ���ͼ����Ѱ� �κ� ������
    StartCharacterPacket,   //�α��εǼ� ����ĳ���͸� �����Ѱ�
    AccountPacket, // ȸ������
    ClientReadyPacket,
    ClientPlayerPacket, // �� �ڽ��� ������Ʈ �ش޶�� ��Ŷ
    GetRankPacket, // ��ŷ�� �����޶�� ��Ŷ
    DeleteCharacterPacket, // ����
    MAX,
};


enum class SERVERTOCLIENTTYPE : int
{
    AccountResultPacket,
    LoginResultPacket,
    CharacterPacket,
    CharacterUpdatePacket,
    SelectUpdatePacket,
    PlayerUpdateDataPacket, // �ٸ� �����鿡�� ���� ��Ŷ
    PlayerUpdatePacket, // �ٸ� �����鿡�� ���� ��Ŷ
    GameStartPacket,
    MonsterUpdateDataPacket, // ���͸� ������ ������Ʈ�ϰ� �����.
    MonsterUpdatePacket, // ���͸� ������ ������Ʈ�ϰ� �����.
    ItemUpdatePacket, // 
    //PotalUpdatePacket, // 
    WorldMoveOKPacket, // 
    RankPacket, // 
    PlayerDeathPacket,
    MAX,
};

enum class ActorState : int
{
    Wait,
    in,
    Update,
    Att, // ������Ʈ�� ���ÿ� ó���ȴ�.
    Death,
    WorldMove,
};