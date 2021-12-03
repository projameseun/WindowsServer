#pragma once
#include <TcpConnecter.h>
#include <vector>
#include <list>

enum ITEMDBCHECKTYPE
{
    NEW,
    UPDATE,
    NONE,
};

// �з�1 : 
// �з�2 : 
// �뵵 : 
// ���� : 
class Actor;
class CharacterTableData;
class ItemTableData;
class ItemData;
class LogicConnecter : public TcpConnecter
{
private: // Static Var
public: // Static Func
private: // member Var

    std::shared_ptr<CharacterTableData> m_CharacterData;

    //�ϴ� ��������ǵ� ���ݺ��ʹ� ĳ���Ͱ� �ϳ����ƴ϶� �ϳ��̻��̵ɼ��ֱ⶧���� vector�θ����
    std::vector<std::shared_ptr<CharacterTableData>> m_CharacterDatas;
    // ��ø�Ǵ� ������ ������ ���� �˻��ϱ� ���� �ڷᱸ�� 
    std::list<std::shared_ptr<ItemTableData>> m_PotionItemsData;
    std::list<ITEMDBCHECKTYPE*> m_PotionItemsDataUpdateData;

    // ���� �������� �ڷᱸ��
    std::vector<std::shared_ptr<ItemTableData>> m_ItemsData;
    std::vector<ITEMDBCHECKTYPE> IsUpdate;

    // ��ȯ ������ �������ؼ� weak_ptr�� �޴´�.
    std::weak_ptr<Actor> m_Actor;

    //
public:
    std::shared_ptr<Actor> GetActor()
    {
        return m_Actor.lock();
    }

    void SetActor(std::shared_ptr<Actor> _Actor)
    {
        m_Actor = _Actor;
    }

    std::vector<std::shared_ptr<CharacterTableData>>  GetCharacterDatas()
    {
        return m_CharacterDatas;
    }

    std::shared_ptr<CharacterTableData> GetCharacterData()
    {
        return m_CharacterData;
    }

    std::vector<std::shared_ptr<ItemTableData>> GetItemsData()
    {
        return m_ItemsData;
    }

    std::vector<std::shared_ptr<ItemTableData>>& GetItemsDataRef()
    {
        return m_ItemsData;
    }

    std::vector<ITEMDBCHECKTYPE>& GetItemsDataCheckRef()
    {
        return IsUpdate;
    } 

    void SetCharacterDatas(std::vector<std::shared_ptr<CharacterTableData>> _CharacterDatas)
    {
        m_CharacterDatas = _CharacterDatas;
    }

    void SetCharacterData(std::shared_ptr<CharacterTableData> _CharacterData)
    {
        m_CharacterData = _CharacterData;
    }

    void LogicDataReset() 
    {
        m_CharacterData = nullptr;
        ItemDataReset();
    }

    void SetItemsData(std::vector<std::shared_ptr<class ItemTableData>> _ItemsDatas);
    void PushItemData(ItemData& _Data);
    void ItemDataReset();


private:
    void NewItemData(ItemData& _Data);

public: // constructer destructer
    LogicConnecter();
    ~LogicConnecter();

public: // delete constructer 
    LogicConnecter(const LogicConnecter& _Other) = delete;
    LogicConnecter(const LogicConnecter&& _Other) = delete;

public: // delete operator
    LogicConnecter& operator=(const LogicConnecter& _Other) = delete;
    LogicConnecter& operator=(const LogicConnecter&& _Other) = delete;

public: // member Func
};

