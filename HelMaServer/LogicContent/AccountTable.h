#pragma once
#include <GameEngineMemory.h>
#include <GameEngineString.h>
#include <GameEngineThread.h>
#include <map>
#include <DBRowData.h>


class AccountTableData : public DBRowData
{
public:
    __int64 PID;
    __int64     CharacterSize;   //4�����ִ���
    char Name[45];
    char Password[45];

public:
    AccountTableData()
    {
        // ��������� �Ǹ� �̳༮�� �ɹ��� �� ���ε� �Ǿ� �ִ�.
        MemberBind<DB__Int64>(&PID);
        MemberBind<DB__Int64>(&CharacterSize);
        MemberBind<DBchar<45>>(&Name[0]);
        MemberBind<DBchar<45>>(&Password[0]);
    }
};

// ���̺��� ������ ������ִ� �뵵�� ����ϰڽ��ϴ�.
class AccountTable 
{
private:
public: 
public: 
    // �̰� �̸����� ã�� ������ ������ִ� ����Դϴ�.
    static std::string SelectQueryCreate(GameEngineString _Name);
    static std::string InsertQueryCreate(GameEngineString _Name, GameEngineString _Pass, __int64 _CharacterSize);
    static std::string UpdateQueryCreate(AccountTableData& _Data);

    // static std::string DeleteQueryCreate(GameEngineString _PID);

private: 
    AccountTable();
    ~AccountTable();

public: // delete constructer 
    AccountTable(const AccountTable& _Other) = delete;
    AccountTable(const AccountTable&& _Other) = delete;

public: // delete operator
    AccountTable& operator=(const AccountTable& _Other) = delete;
    AccountTable& operator=(const AccountTable&& _Other) = delete;
};

