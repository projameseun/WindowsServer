#include "AccountTable.h"

// Static Var
// Static Func

// constructer destructer
AccountTable::AccountTable() 
{

}

AccountTable::~AccountTable() 
{

}

std::string AccountTable::SelectQueryCreate(GameEngineString _Name) 
{
    std::string Name = _Name.GetConvertMultiByteString();
    std::string NewQuery = "SELECT PID,CharacterSize, Name, Password FROM helmaserver.accounttable WHERE Name = '";
    NewQuery += Name + "'";
    return NewQuery;
}

std::string AccountTable::InsertQueryCreate(GameEngineString _Name, GameEngineString _Pass, __int64 _CharacterSize)
{
    // INSERT INTO `server11`.`accounttable` (`Name`, `Password`) VALUES('j', 'j');

    std::string Name = _Name.GetConvertMultiByteString();
    std::string CharacterSize = std::to_string(_CharacterSize);
    std::string Password = _Name.GetConvertMultiByteString();


    std::string NewQuery = "INSERT INTO helmaserver.accounttable (Name,CharacterSize, Password) VALUES('";
    NewQuery += Name + "', '";
    NewQuery += CharacterSize + "','";
    NewQuery += Password + "')";
    return NewQuery;
}


std::string AccountTable::UpdateQueryCreate(AccountTableData& _Data)
{
    //여기서 캐릭터 사이즈 변경됫을때 업데이트
    std::vector<DBVar*>& Data = _Data.GetDBVarData();
   
   // UPDATE `helmaserver`.`accounttable` SET `CharacterSize` = '3' WHERE(`PID` = '3');
    return "UPDATE helmaserver.accounttable SET CharacterSize = '"
        + Data[1]->ToString() + "' WHERE(PID = '"
        + Data[0]->ToString() + "');";

}