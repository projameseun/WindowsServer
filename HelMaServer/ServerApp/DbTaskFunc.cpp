#include "DbTaskFunc.h"
#include <DBManager.h>
#include <AccountTable.h>
#include <CharacterTable.h>
#include <ClientToServer.h>
#include "ServerConnecter.h"
#include "GameEngineServer.h"
#include <LogicValue.h>
#include "ServerTaskFunc.h"
#include <ItemTable.h>
#include <CharacterTable.h>
// Static Var
// Static Func


void DbTaskFunc::LoginSelectProcess(DBConnecter* Connecter, DBTask* _Ptr, 
    LoginPacket _Data, ServerConnecter* _Socket)
{
    std::vector<std::shared_ptr<AccountTableData>> Data;
    Connecter->DynamicQueryTemplate(_Ptr->Query.c_str(), Data);

    // DB���� �����͸� ������ �˴ϴ�.

    // �ƿ� �� ĳ���Ͱ� �������� �ʴ´�.
    if (0 >= Data.size())
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, 
            [_Ptr, _Socket]()
            {
                // DB������
                LoginResultPacket Pacekt;
                Pacekt.m_Code = (int)LoginResultType::IDERROR;
                _Socket->Send(Pacekt);

                //[Data]() 
                //{
                //    // ��Ŷ������
                //};

                DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
            });

        return;
    }

     if (1 < Data.size())
    {
        // �� ������ �ɰ��� ���� 2���� ���ü� ����.

        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
            {
                LoginResultPacket Pacekt;
                Pacekt.m_Code = (int)LoginResultType::ServerError;
                _Socket->Send(Pacekt);
                DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
            });

        return;
    }

    std::shared_ptr<AccountTableData> AccountData = Data[0];

    if (nullptr == AccountData)
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
            {
                LoginResultPacket Pacekt;
                Pacekt.m_Code = (int)LoginResultType::ServerError;
                _Socket->Send(Pacekt);
                DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
            });

        return;
    }

    //������ ���࿡ �̹� ��������� �̹�ĳ���Ͱ� �ִٸ��� 
    //���⿡ ���� ĳ���� ��Ŷ�� ������Ե˴ϴ�.
    //���ٸ� �׳� �ƹ��͵� �����ʽ��ϴ�
    std::vector<std::shared_ptr<CharacterTableData>> ChData;

    Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ChData);

   

    //���߿��������ʿ��ϸ�׶���
   //std::vector<std::shared_ptr<ItemTableData>> ItemDatas;
   //Connecter->DynamicQueryTemplate(ItemTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ItemDatas);

    GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, 
        std::bind(&ServerTaskFunc::LoginOKProcess, AccountData,ChData,_Socket));

    // �� ����� �� �������� ��Ƽ� �����ų�.
    
    // ���� ������� �����
    // Packet Task�� ������ Post�� �̿��� ó���� �ϰڽ��ϴ�.

    
    // _Socket->Send()
    // ���⿡�� �׳� �ٽ� ��Ŷó�����·� �����Ҽ� �ְ�
}

void DbTaskFunc::SelectCharacterProcess(DBConnecter* Connecter, DBTask* _Ptr, ServerConnecter* _Socket)
{
    //���⼭ ĳ�������̺��� ������µ� ��PID�� �´°Ÿ� ���´ٱ״�����
    //�г����� ���ؼ� �״г����� �־��־ߵ�
    std::vector<std::shared_ptr<AccountTableData>> Data;
    Connecter->DynamicQueryTemplate(_Ptr->Query.c_str(), Data);

    // DB���� �����͸� ������ �˴ϴ�.
    //������ �α��εȰ�Ȯ�εǼ� ����ó������

    std::shared_ptr<AccountTableData> AccountData = Data[0];

    if (nullptr == AccountData)
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
            {
                LoginResultPacket Pacekt;
                Pacekt.m_Code = (int)LoginResultType::ServerError;
                _Socket->Send(Pacekt);
                DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
            });

        return;
    }

    std::vector<std::shared_ptr<CharacterTableData>> ChDatas;
    Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ChDatas);

    //ĳ���͵��� �� �����ݴϴ� 

    {
        std::vector<CharacterPacket> NewCharacterPacket;

        NewCharacterPacket.resize(ChDatas.size());

        SelectUpdatePacket UpdateCharactetPacket;

        for (size_t i = 0; i < ChDatas.size(); i++)
        {
            NewCharacterPacket[i].PID = ChDatas[i]->PID;
            NewCharacterPacket[i].NAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->Name);
            NewCharacterPacket[i].NICKNAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->NickName);
            NewCharacterPacket[i].CHARACTERNAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->CharacterName);
            NewCharacterPacket[i].EndIndex = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->EndIndex);
            NewCharacterPacket[i].LastX = ChDatas[i]->LastX;
            NewCharacterPacket[i].LastY = ChDatas[i]->LastY;
            NewCharacterPacket[i].MaxHp = ChDatas[i]->MAXHP;
            NewCharacterPacket[i].Hp = ChDatas[i]->HP;
            NewCharacterPacket[i].Att = ChDatas[i]->ATT;

            UpdateCharactetPacket.m_CharacterData.push_back(NewCharacterPacket[i]);

        }

        if (SOCKET_ERROR == _Socket->Send(UpdateCharactetPacket))
        {
            int a = 0;
        }
    }

   /* std::vector<std::shared_ptr<ItemTableData>> ItemDatas;
    Connecter->DynamicQueryTemplate(ItemTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ItemDatas);*/

    
   // GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT,
       // std::bind(&ServerTaskFunc::MainStartProcess, ChDatas[0], _Socket));

 
}

void DbTaskFunc::StartCharacterProcess(DBConnecter* Connecter, DBTask* _Ptr, StartCharacterPacket _Data, ServerConnecter* _Socket)
{


    //���⼭ ĳ�������̺��� ������µ� ��PID�� �´°Ÿ� ���´ٱ״�����
    //�г����� ���ؼ� �״г����� �־��־ߵ�
    std::vector<std::shared_ptr<AccountTableData>> Data;
    Connecter->DynamicQueryTemplate(_Ptr->Query.c_str(), Data);

    // DB���� �����͸� ������ �˴ϴ�.
    //������ �α��εȰ�Ȯ�εǼ� ����ó������

    std::shared_ptr<AccountTableData> AccountData = Data[0];

    if (nullptr == AccountData)
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
            {
                LoginResultPacket Pacekt;
                Pacekt.m_Code = (int)LoginResultType::ServerError;
                _Socket->Send(Pacekt);
                DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
            });

        return;
    }

    std::vector<std::shared_ptr<CharacterTableData>> ChDatas;
    Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ChDatas);

    //ĳ���͵��� �� �����ݴϴ� 

    {
        CharacterPacket NewCharacterPacket;

        NewCharacterPacket;

        /// CharacterUpdatePacket UpdateCharactetPacket;

        for (size_t i = 0; i < ChDatas.size(); i++)
        {
            if (ChDatas[i]->NickName == _Data.NICKNAME.GetConvertMultiByteString())
            {
                NewCharacterPacket.PID = ChDatas[i]->PID;
                NewCharacterPacket.NAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->Name);
                NewCharacterPacket.NICKNAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->NickName);
                NewCharacterPacket.CHARACTERNAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->CharacterName);
                NewCharacterPacket.EndIndex = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->EndIndex);
                NewCharacterPacket.LastX = ChDatas[i]->LastX;
                NewCharacterPacket.LastY = ChDatas[i]->LastY;
                NewCharacterPacket.MaxHp = ChDatas[i]->MAXHP;
                NewCharacterPacket.Hp = ChDatas[i]->HP;
                NewCharacterPacket.Att = ChDatas[i]->ATT;

                GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT,
                    std::bind(&ServerTaskFunc::MainStartProcess, ChDatas[i], _Socket));

                //UpdateCharactetPacket.m_CharacterData.push_back(NewCharacterPacket);

            }
        }
      

    }
}


void DbTaskFunc::DisConnectDataUpdateProcess(DBConnecter* Connecter, DBTask* _Ptr, std::shared_ptr<CharacterTableData> _CharacterData, std::vector<std::shared_ptr<ItemTableData>> _Item, std::vector<ITEMDBCHECKTYPE> _ItemCheck)
{
    {
        std::string UpdateQuery = CharacterTable::UpdateQueryCreate(*_CharacterData);
        Connecter->DynamicQuery(UpdateQuery.c_str());
    }

    /*{
        for (size_t i = 0; i < _ItemCheck.size(); i++)
        {
            if (ITEMDBCHECKTYPE::UPDATE == _ItemCheck[i])
            {
                std::string ItemUpdateQuery = ItemTable::UpdateQueryCreate(*_Item[i]);
                Connecter->DynamicQuery(ItemUpdateQuery.c_str());
            }
            else if (ITEMDBCHECKTYPE::NEW == _ItemCheck[i])
            {
                std::string ItemInsertQuery = ItemTable::InsertQueryCreate(*_Item[i]);
                Connecter->DynamicQuery(ItemInsertQuery.c_str());
            }
        }
    }*/
}

void DbTaskFunc::DeleteCharacterProcess(DBConnecter* Connecter, DBTask* _Ptr, DeleteCharacterPacket _Data, ServerConnecter* _Socket)
{
 
    //ĳ���ͻ����� �����
    std::vector<std::shared_ptr<AccountTableData>> Data;

    Connecter->DynamicQueryTemplate(AccountTable::SelectQueryCreate(_Data.ID).c_str(), Data);

    std::shared_ptr< AccountTableData> AccountData = Data[0];


    Data[0]->CharacterSize -= 1;
    //���⼭ ������Ʒ ��� 

    std::string UpdateQuery = AccountTable::UpdateQueryCreate(*AccountData);
    Connecter->DynamicQuery(UpdateQuery.c_str());


    if (nullptr == AccountData)
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, [_Ptr, _Socket]()
            {
                LoginResultPacket Pacekt;
                Pacekt.m_Code = (int)LoginResultType::ServerError;
                _Socket->Send(Pacekt);
                DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
            });

        return;
    }

    std::vector<std::shared_ptr<CharacterTableData>> ChDatas;
    Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ChDatas);

    //ĳ���͵��� �� �����ݴϴ� 

    std::vector<CharacterPacket> NewCharacterPacket;

    NewCharacterPacket.resize(ChDatas.size());

    SelectUpdatePacket UpdateCharactetPacket;

    {




        for (size_t i = 0; i < ChDatas.size(); i++)
        {
            if (ChDatas[i]->NickName == _Data.NICKNAME.GetConvertMultiByteString())
            {

                Connecter->DynamicQueryTemplate(CharacterTable::DeleteQueryCreate((ChDatas[i]->no)).c_str(), ChDatas);


            }

            else
            {
                NewCharacterPacket[i].PID = ChDatas[i]->PID;
                NewCharacterPacket[i].NAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->Name);
                NewCharacterPacket[i].NICKNAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->NickName);
                NewCharacterPacket[i].CHARACTERNAME = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->CharacterName);
                NewCharacterPacket[i].EndIndex = GameEngineString::GlobalSetConvertMultiByteString(ChDatas[i]->EndIndex);
                NewCharacterPacket[i].LastX = ChDatas[i]->LastX;
                NewCharacterPacket[i].LastY = ChDatas[i]->LastY;
                NewCharacterPacket[i].MaxHp = ChDatas[i]->MAXHP;
                NewCharacterPacket[i].Hp = ChDatas[i]->HP;
                NewCharacterPacket[i].Att = ChDatas[i]->ATT;

                UpdateCharactetPacket.m_CharacterData.push_back(NewCharacterPacket[i]);
            }



        }
        if (SOCKET_ERROR == _Socket->Send(UpdateCharactetPacket))
        {
            int a = 0;
        }
        //�ٽ� ĳ���͸� �����°� �ٽ� �����ߵȴ� �����̵����ϱ�

    }
}