// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Start.h"
#include "Sockets.h"
#include "UEServerConnect.h"
#include "HelMaGameInstance.h"
#include <string>
#include <GameEngineString.h>
#include <GameEngineDirectory.h>
#include <GameEngineFile.h>
//#include "UnActorManager.h"
#include <ClientToServer.h>
//#include "MainActor.h"
#include "UEServerConnect.h"
#include "Components/TextBlock.h"
#include <LogicValue.h>

FString UWidget_Start::IPText;
FString UWidget_Start::IDText;
FString UWidget_Start::PASSText;


void UWidget_Start::NativePreConstruct()
{
	Super::NativePreConstruct();

	IPLoad();
}

void UWidget_Start::NativeConstruct()
{
	Super::NativeConstruct();

	fTime = 3.f;

	bTime = false;

	m_LoginText = Cast<UTextBlock>(GetWidgetFromName(TEXT("LoginTxt")));

	if (IsValid(m_LoginText))
	{
		m_LoginText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UWidget_Start::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (1 == UEServerConnect::GetInst().m_Login)
	{
	   UGameplayStatics::OpenLevel(GetWorld(), TEXT("Select"));
	}

	if (bTime)
	{
		fTime -= InDeltaTime;
		if (0 >= fTime)
		{
			m_LoginText->SetVisibility(ESlateVisibility::Hidden);
			fTime = 3.f;
			bTime = false;
		}
	}
	
	
}

void UWidget_Start::NotLoginText()
{
	bTime = true;
	m_LoginText->SetVisibility(ESlateVisibility::Visible);
}

void UWidget_Start::ConnectButtonCallback()
{
	LOG(L"ConnectButtonCallback");

	IPText = m_IP.ToString();
	IPSave();
	UEServerConnect::GetInst().ConnectTaskStart();
}


void UWidget_Start::LoginButtonCallback()
{
	LOG(L"LoginButtonCallback");

	LoginPacket NewPacket;

	NewPacket.ID = *m_ID.ToString();
	NewPacket.PASS = *m_Password.ToString();

	IDText = m_ID.ToString();
	PASSText = m_Password.ToString();

	if (false == UEServerConnect::GetInst().IsConnect())
	{
		LOGERROR(L"Is Not Connect ID %s | PW %s", *m_ID.ToString(), *m_Password.ToString());

		m_LoginText->SetVisibility(ESlateVisibility::Visible);
		bTime = true;
	}
	else
	{
		// AMainActor::GetInst().IsMouseCenter = true;
		UEServerConnect::GetInst().Send(NewPacket);
		LOG(L"Is Login Packet Send ID %s | PW %s", *m_ID.ToString(), *m_Password.ToString());
		
		
		
	}
}


void UWidget_Start::SingleButtonCallback()
{
	LOG(L"SingleButtonCallback");
}


void UWidget_Start::AccountButtonCallback()
{
	LOG(L"AccountButtonCallback");

	if (m_ID.ToString() == TEXT("") || m_Password.ToString() == TEXT(""))
	{
		return;
	}

	AccountPacket NewPacket;
	NewPacket.ID = *m_ID.ToString();
	NewPacket.PASS = *m_Password.ToString();
	UEServerConnect::GetInst().Send(NewPacket);
	LOG(L"ULoginScreenWidget::AccountProgress() ID %s | PW %s", *m_ID.ToString(), *m_Password.ToString());
}

void UWidget_Start::IPSave()
{
	// UE_LOG(LogTemp, Error, L"void ULoginScreenWidget::BeginPlay() ");
	GameEngineDirectory NewDir;

	// 내가 만든 코드를 언리얼에서 사용하는 거니까 위험할수도 있으니
	GameEngineFile NewFile = NewDir.GetFile(L"IPSAVE.Data");

	FString FStringText = m_IP.ToString();

	GameEngineString Text = (*FStringText);

	NewFile.FileOpen(L"wb");
	NewFile << Text;
}


void UWidget_Start::IPLoad()
{
	TArray<int> ARR;
	for (size_t i = 0; i < 10; i++)
	{
		ARR.Add(i);
	}

	for (size_t i = 0; i < 10; i++)
	{
		UE_LOG(LogTemp, Error, L"%d", ARR[i]);
	}


	// UE_LOG(LogTemp, Error, L"void ULoginScreenWidget::BeginPlay() ");
	GameEngineDirectory NewDir;

	// 내가 만든 코드를 언리얼에서 사용하는 거니까 위험할수도 있으니
	GameEngineFile NewFile = NewDir.GetFile(L"IPSAVE.Data");

	GameEngineString Text;
	if (true == NewFile.IsExist())
	{
		NewFile.FileOpen(L"rb");
		NewFile >> Text;

		m_IP = FText::FromString(Text.ConstStringPtr());

		return;
	}

	return;
}

