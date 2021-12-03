#pragma once
// #include <ClientToServer.h>
#include <memory>
#include <vector>


// 분류1 : 
// 분류2 : 
// 용도 : 
// 설명 : 
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
    // DB요청의 결과를 어떻게 처리할지를 결정하는 함수들을 모아놓을 겁니다.
};

