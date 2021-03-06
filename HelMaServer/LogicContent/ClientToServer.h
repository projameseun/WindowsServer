#pragma once
#include "PacketType.h"
#include <GEMath.h>


// 여기서 만드는 녀석들은 전부다 
class LoginPacket : public ClientToServer
{
public:
    GameEngineString ID;
    GameEngineString PASS;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << ID;
        Ser << PASS;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override 
    {
        ClientToServer::Serialize(_Ser);
        _Ser << ID;
        _Ser << PASS;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> ID;
        _Ser >> PASS;
    }

public:
    LoginPacket() : ClientToServer(CLIENTTOSERVERTYPE::LoginPacket)
    {
    }

    virtual ~LoginPacket() 
    {
    }
};

class SelectCharacterPacket : public ClientToServer
{
public:
    GameEngineString ID;
    GameEngineString PASS;
    GameEngineString NICKNAME;
    GameEngineString CHARACTERNAME;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << ID;
        Ser << PASS;
        Ser << NICKNAME;
        Ser << CHARACTERNAME;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << ID;
        _Ser << PASS;
        _Ser << NICKNAME;
        _Ser << CHARACTERNAME;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> ID;
        _Ser >> PASS;
        _Ser >> NICKNAME;
        _Ser >> CHARACTERNAME;
    }

public:
    SelectCharacterPacket() : ClientToServer(CLIENTTOSERVERTYPE::SelectCharacterPacket)
    {
    }

    virtual ~SelectCharacterPacket()
    {
    }
};

//실제 캐릭터를 선택하고 실행해서 들어갓을대
class StartCharacterPacket : public ClientToServer
{
public:
    GameEngineString ID;
    GameEngineString PASS;
    GameEngineString NICKNAME;
    GameEngineString CHARACTERNAME;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << ID;
        Ser << PASS;
        Ser << NICKNAME;
        Ser << CHARACTERNAME;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << ID;
        _Ser << PASS;
        _Ser << NICKNAME;
        _Ser << CHARACTERNAME;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> ID;
        _Ser >> PASS;
        _Ser >> NICKNAME;
        _Ser >> CHARACTERNAME;
    }

public:
    StartCharacterPacket() : ClientToServer(CLIENTTOSERVERTYPE::StartCharacterPacket)
    {
    }

    virtual ~StartCharacterPacket()
    {
    }
};


class AccountPacket : public ClientToServer
{
    // 내가 이렇게 맴버변수만 선언해도

public:
    GameEngineString ID;
    GameEngineString PASS;
    __int64          CharacterSize;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << ID;
        Ser << PASS;
        Ser << CharacterSize;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << ID;
        _Ser << PASS;
        _Ser << CharacterSize;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> ID;
        _Ser >> PASS;
        _Ser >> CharacterSize;
    }

public:
    AccountPacket() : ClientToServer(CLIENTTOSERVERTYPE::AccountPacket)
    {
    }

    ~AccountPacket()
    {
    }
};


class ClientReadyPacket : public ClientToServer
{
    // 내가 이렇게 맴버변수만 선언해도

public:
    int m_Code;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << m_Code;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << m_Code;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> m_Code;
    }

public:
    ClientReadyPacket() : ClientToServer(CLIENTTOSERVERTYPE::ClientReadyPacket)
    {
    }

    ~ClientReadyPacket()
    {
    }
};

class ClientPlayerPacket : public ClientToServer
{
public:
    __int64 UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
    ActorState m_State; // 코드를 구분할수 있는 값
    int Order; // 어떠한 플레이어에게 붙은 고유의 값.
    ActorUpdateData ActorData;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        Ser << m_State; // 코드를 구분할수 있는 값
        Ser << Order; // 어떠한 플레이어에게 붙은 고유의 값.
        ActorData.Serialize(Ser);
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser << m_State; // 코드를 구분할수 있는 값
        _Ser << Order; // 어떠한 플레이어에게 붙은 고유의 값.
        ActorData.Serialize(_Ser);
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> UpdateID; // 어떠한 플레이어에게 붙은 고유의 값.
        _Ser >> m_State; // 코드를 구분할수 있는 값
        _Ser >> Order; // 어떠한 플레이어에게 붙은 고유의 값.
        ActorData.DeSerialize(_Ser);
    }

public:
    ClientPlayerPacket() : ClientToServer(CLIENTTOSERVERTYPE::ClientPlayerPacket)
    {
    }

    virtual ~ClientPlayerPacket()
    {
    }
};


class GetRankPacket : public ClientToServer
{
public:
    // 0 TopRank;
    // 1 UserRank;
    int Type;

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << Type;
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << Type;
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> Type;
    }

public:
    GetRankPacket() : ClientToServer(CLIENTTOSERVERTYPE::GetRankPacket)
    {
    }

};


class DeleteCharacterPacket : public ClientToServer
{
public:
    GameEngineString ID;
    GameEngineString PASS;
    GameEngineString NICKNAME;
    //__int64         Number;
    

public:
    GameEngineSerializer Serialize() override
    {
        GameEngineSerializer Ser;
        ClientToServer::Serialize(Ser);
        Ser << ID;
        Ser << PASS;
        Ser << NICKNAME;
    
        Ser.ChangeToOffset(8);
        return Ser;
    }

    void Serialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::Serialize(_Ser);
        _Ser << ID;
        _Ser << PASS;
        _Ser << NICKNAME;
  
        _Ser.ChangeToOffset(8);
    }

    void DeSerialize(GameEngineSerializer& _Ser) override
    {
        ClientToServer::DeSerialize(_Ser);
        _Ser >> ID;
        _Ser >> PASS;
        _Ser >> NICKNAME;

    }

public:
    DeleteCharacterPacket() : ClientToServer(CLIENTTOSERVERTYPE::DeleteCharacterPacket)
    {
    }

    virtual ~DeleteCharacterPacket()
    {
    }
};