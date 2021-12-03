// Fill out your copyright notice in the Description page of Project Settings.


#include "UEResManager.h"


UEResManager::UEResManager()
{
}

UEResManager::~UEResManager()
{
    
}

UTexture2D* UEResManager::GetIconImage(int _Index)
{
    if (0 > _Index || _Index >= m_CharacterImgArray.Num())
    {
        return nullptr;
    }


    return m_CharacterImgArray[_Index];
}

void UEResManager::ResInit()
{
    UE_LOG(LogTemp, Error, L"UnResManager::ResInit()");

    m_CharacterImgArray.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/UI/KallariImg.KallariImg'")));
    m_CharacterImgArray.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/UI/PhaseImg.PhaseImg'")));
    m_CharacterImgArray.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/UI/ShinbiImg.ShinbiImg'")));
    

    for (size_t i = 0; i < m_CharacterImgArray.Num(); i++)
    {
        if (nullptr != m_CharacterImgArray[i])
        {
            UE_LOG(LogTemp, Error, TEXT("Res Load OK %d"), i);
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Res Load %d"), m_CharacterImgArray.Num());

}

void UEResManager::Release()
{
    UE_LOG(LogTemp, Error, L"UnResManager::Release()");
    m_CharacterImgArray.Empty();
}