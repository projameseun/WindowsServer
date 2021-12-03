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
        //�̹�ĳ���Ͱ� �����Ѵٴ°�
        Con->SetCharacterDatas(Data);
        //�ϴ��� ����� ��������������� 0,0�� �־��ְٽ��ϴ�
        LogicThread::InsertMessage(_ChData[0]->EndIndex, &WorldMsgFunc::SelectPlayerCreate,Con);

    }

    //����Ŀ��Ʈ���ϰ� �α��θ��ϴ°��̴� �α����̵Ǹ� Ŭ�󿡼�\
    ĳ����select �� �ϰԵɰŴ�
   

}

void ServerTaskFunc::MainStartProcess(std::shared_ptr<CharacterTableData> _Data,ServerConnecter* Con)
{
    //�α������̰� ĳ���͸� ������ ��������������
    //Ŭ�󿡼� ������ ���������� �����°� �׸��� �׋� ĳ���͸� ������ְ� �����Ѵ�
    Con->SetCharacterData(_Data);
    LogicThread::InsertMessage(
        _Data->EndIndex,
        &WorldMsgFunc::WaitPlayerCreate, Con);
}