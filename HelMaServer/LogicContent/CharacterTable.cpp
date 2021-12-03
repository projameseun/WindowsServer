#include "CharacterTable.h"


std::string CharacterTable::SelectQueryCreate(const std::string& _PID)
{
    std::string ID = _PID;
    std::string NewQuery = "SELECT no, PID, Name,NickName,CharacterName, EndIndex, LastX, LastY, ATT, HP, MAXHP, Score FROM helmaserver.characterdatatable WHERE PID = '";
    NewQuery += ID + "'";
    return NewQuery;
}

std::string CharacterTable::InsertQueryCreate(CharacterTableData& _Data) 
{
    // INSERT INTO server11.characterdatatable (PID, Name, EndIndex, LastX, LastY, ATT, HP, MAXHP) VALUES('2', 'f', '0,0', '5', '5', '100', '100', '100');

    // INSERT INTO server11.characterdatatable(PID, Name, EndIndex, LastX, LastY, ATT, HP, MAXHP) VALUES('2', 'f', '0,0', '5', '5', '100', '100', '100');
    std::string NewQuery = "INSERT INTO helmaserver.characterdatatable(PID, Name,NickName,CharacterName, EndIndex, LastX, LastY, ATT, HP, MAXHP, Score) VALUES(";
    std::vector<DBVar*>& Data = _Data.GetDBVarData();
    for (size_t i = 1; i < Data.size(); i++)
    {
        NewQuery += "'";
        NewQuery += Data[i]->ToString();
        NewQuery += "'";

        if (i == Data.size()-1)
        {
            break;
        }

        NewQuery += ",";
    }

    NewQuery += ")";

    return NewQuery;
}

std::string CharacterTable::UpdateQueryCreate(CharacterTableData& _Data) 
{
    std::vector<DBVar*>& Data = _Data.GetDBVarData();

    //std::string Query =
    //    "UPDATE server11.characterdatatable SET EndIndex = '"
    //    + Data[3]->ToString() + "', ATT = '"
    //    + Data[4]->ToString() + "', HP = '"
    //    + Data[5]->ToString() + "', MAXHP = '"
    //    + Data[6]->ToString() + "' WHERE(no = '"
    //    + Data[0]->ToString() + "');";


    // UPDATE server11.characterdatatable SET LastX = '7', LastY = '3' WHERE(no = 2);

    return "UPDATE helmaserver.characterdatatable SET EndIndex = '"
        + Data[5]->ToString() + "', LastX = '"
        + Data[6]->ToString() + "', LastY = '"
        + Data[7]->ToString() + "', ATT = '"
        + Data[8]->ToString() + "', HP = '"
        + Data[9]->ToString() + "', MAXHP = '"
        + Data[10]->ToString() + "', Score = '"
        + Data[11]->ToString() + "' WHERE(no = '"
        + Data[0]->ToString() + "');";
}



std::string CharacterTable::DeleteQueryCreate(__int64  _no)
{
   
    std::string NewQuery = "DELETE FROM helmaserver.characterdatatable WHERE(no = '"
        + std::to_string(_no) + "');";
    return NewQuery;
}

//DELETE FROM `helmaserver`.`characterdatatable` WHERE(`no` = '3');