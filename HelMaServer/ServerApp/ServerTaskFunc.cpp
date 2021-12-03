#include "ServerTaskFunc.h"
#include <DBManager.h>
#include <AccountTable.h>
#include <ClientToServer.h>
#include <ServerConnecter.h>
#include "GameEngineServer.h"
#include <LogicValue.h>
#include "LogicThread.h"
#include "WorldMsgFunc.h"

// Static Var
// Static Func


void ServerTaskFunc::LoginOKProcess(std::shared_ptr<AccountTableData> _Data, 
    std::vector<std::shared_ptr<CharacterTableData>> _ChData,
    ServerConnecter* Con)
{
    LoginResultPacket OKPacket;
    OKPacket.m_Code = (int)LoginResultType::OK;
    

  //  Con->SetCharacterData(_ChData);

    
    if (SOCKET_ERROR == Con->Send(OKPacket))
    {
        int a = 0;
    }

    std::vector<std::shared_ptr<CharacterTableData>> Data = _ChData;
    if (0 != Data.size())
    {
        //이미캐릭터가 존재한다는거
        Con->SetCharacterDatas(Data);
        //일단은 월드는 딱히뭐없어서강제로 0,0를 넣어주겟습니다
        LogicThread::InsertMessage(_ChData[0]->EndIndex, &WorldMsgFunc::SelectPlayerCreate,Con);

    }

    //서버커넥트를하고 로그인만하는곳이다 로그인이되면 클라에서\
    캐릭터select 를 하게될거다
   

}

void ServerTaskFunc::MainStartProcess(std::shared_ptr<CharacterTableData> _Data,ServerConnecter* Con)
{
    //로그인은됫고 캐릭터를 선택은 지금은안하지만
    //클라에서 게임을 시작했을대 들어오는곳 그리고 그떄 캐릭터를 만들어주고 세팅한다
    Con->SetCharacterData(_Data);
    LogicThread::InsertMessage(
        _Data->EndIndex,
        &WorldMsgFunc::WaitPlayerCreate, Con);
}