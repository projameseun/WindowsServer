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

    // DB에서 데이터를 얻어오게 됩니다.

    // 아예 이 캐릭터가 존재하지 않는다.
    if (0 >= Data.size())
    {
        GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, 
            [_Ptr, _Socket]()
            {
                // DB쓰레드
                LoginResultPacket Pacekt;
                Pacekt.m_Code = (int)LoginResultType::IDERROR;
                _Socket->Send(Pacekt);

                //[Data]() 
                //{
                //    // 패킷쓰레드
                //};

                DBManager::Inst().m_TaskPool.Push(_Ptr->shared_from_this());
            });

        return;
    }

     if (1 < Data.size())
    {
        // 몬가 굉장히 심각한 오류 2명이 나올수 없다.

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

    //유저가 만약에 이미 만들어졌고 이미캐릭터가 있다면은 
    //여기에 이제 캐릭터 패킷을 갖고오게됩니다.
    //없다면 그냥 아무것도 하지않습니다
    std::vector<std::shared_ptr<CharacterTableData>> ChData;

    Connecter->DynamicQueryTemplate(CharacterTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ChData);

   

    //나중에아이템필요하면그때함
   //std::vector<std::shared_ptr<ItemTableData>> ItemDatas;
   //Connecter->DynamicQueryTemplate(ItemTable::SelectQueryCreate(std::to_string(AccountData->PID)).c_str(), ItemDatas);

    GameEngineServer::GetInst().PushServerTask((int)LogicValue::SERVERTASK::DBRESULT, 
        std::bind(&ServerTaskFunc::LoginOKProcess, AccountData,ChData,_Socket));

    // 이 결과를 또 누구에게 담아서 보낼거냐.
    
    // 가장 상식적인 방법은
    // Packet Task를 날리는 Post를 이용한 처리를 하겠습니다.

    
    // _Socket->Send()
    // 여기에서 그냥 다시 패킷처리형태로 변경할수 있고
}

void DbTaskFunc::SelectCharacterProcess(DBConnecter* Connecter, DBTask* _Ptr, ServerConnecter* _Socket)
{
    //여기서 캐릭터테이블을 갖고오는데 그PID가 맞는거만 갖온다그다음에
    //닉네임을 비교해서 그닉네임을 넣어주야됨
    std::vector<std::shared_ptr<AccountTableData>> Data;
    Connecter->DynamicQueryTemplate(_Ptr->Query.c_str(), Data);

    // DB에서 데이터를 얻어오게 됩니다.
    //무조건 로그인된게확인되서 예외처리없앰

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

    //캐릭터들을 다 보내줍니다 

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


    //여기서 캐릭터테이블을 갖고오는데 그PID가 맞는거만 갖온다그다음에
    //닉네임을 비교해서 그닉네임을 넣어주야됨
    std::vector<std::shared_ptr<AccountTableData>> Data;
    Connecter->DynamicQueryTemplate(_Ptr->Query.c_str(), Data);

    // DB에서 데이터를 얻어오게 됩니다.
    //무조건 로그인된게확인되서 예외처리없앰

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

    //캐릭터들을 다 보내줍니다 

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
 
    //캐릭터사이즈 지우기
    std::vector<std::shared_ptr<AccountTableData>> Data;

    Connecter->DynamicQueryTemplate(AccountTable::SelectQueryCreate(_Data.ID).c_str(), Data);

    std::shared_ptr< AccountTableData> AccountData = Data[0];


    Data[0]->CharacterSize -= 1;
    //여기서 업데이틔 디비 

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

    //캐릭터들을 다 보내줍니다 

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
        //다시 캐릭터를 가져온걸 다시 보내야된다 수정이됫으니까

    }
}