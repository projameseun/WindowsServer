#pragma once
// #include <ClientToServer.h>
#include <memory>
#include <vector>


// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class DBConnecter;
class DBTask;
class LoginPacket;
class ServerConnecter;
class CharacterTableData;
class AccountTableData;

class ServerTaskFunc
{
public:
    static void LoginOKProcess(std::shared_ptr<AccountTableData> _Data, 
        std::vector<std::shared_ptr<CharacterTableData>> _ChData,
        ServerConnecter* Con);
    static void MainStartProcess(std::shared_ptr<CharacterTableData> _Data, ServerConnecter* Con);
    // DB��û�� ����� ��� ó�������� �����ϴ� �Լ����� ��Ƴ��� �̴ϴ�.
};

