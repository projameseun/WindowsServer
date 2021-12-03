// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Select.h"
#include "Widget_Start.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "HelMaGameInstance.h"
#include "Widget_CharacterImg.h"
#include <ClientToServer.h>
#include <GameEngineString.h>
#include "UEResManager.h"
#include "UEServerConnect.h"


int32 UWidget_Select::DataSize;

UWidget_Select* UWidget_Select::SelectWidgetInst = nullptr;

void UWidget_Select::NativePreConstruct()
{
	Super::NativePreConstruct();

	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartBtn")));
	StartButton->OnClicked.AddDynamic(this, &UWidget_Select::GameStartCallback);

	DeleteButton = Cast<UButton>(GetWidgetFromName(TEXT("DeleteBtn")));
	DeleteButton->OnClicked.AddDynamic(this, &UWidget_Select::GameDelteCallback);

	CreateButton0 = Cast<UButton>(GetWidgetFromName(TEXT("CreateBtn0")));
	CreateButton0->OnClicked.AddDynamic(this, &UWidget_Select::CreateButtonCallback0);

	CreateButton1 = Cast<UButton>(GetWidgetFromName(TEXT("CreateBtn1")));
	CreateButton1->OnClicked.AddDynamic(this, &UWidget_Select::CreateButtonCallback1);

	CreateButton2 = Cast<UButton>(GetWidgetFromName(TEXT("CreateBtn2")));
	CreateButton2->OnClicked.AddDynamic(this, &UWidget_Select::CreateButtonCallback2);

	CreateButton3 = Cast<UButton>(GetWidgetFromName(TEXT("CreateBtn3")));
	CreateButton3->OnClicked.AddDynamic(this, &UWidget_Select::CreateButtonCallback3);

	MainCreateButton = Cast<UButton>(GetWidgetFromName(TEXT("MainCreateBtn")));
	MainCreateButton->OnClicked.AddDynamic(this, &UWidget_Select::MainCreateButtonCallback);

	BackButton = Cast<UButton>(GetWidgetFromName(TEXT("BackBtn")));
	BackButton->OnClicked.AddDynamic(this, &UWidget_Select::BackButtonCallBack);

	
	
	

	SelectMainImage = Cast<UImage>(GetWidgetFromName(TEXT("MainSelectImage")));

	MainLevelImage = Cast<UImage>(GetWidgetFromName(TEXT("MainLevelOpenImg")));

	TextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NickBox")));

	m_NoNickName = Cast <UTextBlock> (GetWidgetFromName(TEXT("NoNickName")));

	m_MainLevelText = Cast <UTextBlock>(GetWidgetFromName(TEXT("MainLevelTxt")));


	CharacterImg_Widget0 = Cast<UWidget_CharacterImg>(GetWidgetFromName(TEXT("CharacterImg0")));
	CharacterImg_Widget1 = Cast<UWidget_CharacterImg>(GetWidgetFromName(TEXT("CharacterImg1")));
	CharacterImg_Widget2 = Cast<UWidget_CharacterImg>(GetWidgetFromName(TEXT("CharacterImg2")));
	CharacterImg_Widget3 = Cast<UWidget_CharacterImg>(GetWidgetFromName(TEXT("CharacterImg3")));

	//MainCreateBtn
	StartButton->SetIsEnabled(false);
	DeleteButton->SetIsEnabled(false);
	MainCreateButton->SetIsEnabled(false);

	SelectWidgetInst = this;

	fTime = 3.f;

	bTime = false;

	bLevel = false;
	fMainLevelTime = 2.f;
}

void UWidget_Select::NativeConstruct()
{
	Super::NativeConstruct();

	TextBox->SetVisibility(ESlateVisibility::Hidden);
	MainCreateButton->SetVisibility(ESlateVisibility::Hidden);
	BackButton->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget0->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget1->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget2->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget3->SetVisibility(ESlateVisibility::Hidden);

	CreateString = L"NewCreate";
	CreateString1 = L"NewCreate";
	CreateString2 = L"NewCreate";
	CreateString3 = L"NewCreate";

	m_NoNickName->SetVisibility(ESlateVisibility::Hidden);

	
	
}

void UWidget_Select::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry,InDeltaTime);

	//if (0 == UEServerConnect::GetInst().m_Login)
	//{
	//	StartButton->SetVisibility(ESlateVisibility::Visible);
	//}
	//else if (1 == UEServerConnect::GetInst().m_Login)
	//{
	//	StartButton->SetVisibility(ESlateVisibility::Visible);
	//}

	//���࿡ ĳ���Ͱ� �մٸ� �׹�ư�� �űԻ��� ���� �Ѿ�����ϰ��ϰ� 
	//�ٷ� Ŭ���ϰ� ��ŸƮ�� Ȱ��ȭ���ǰ� �ϰ� �ٷν����Ѵ� 

	if (bTime)
	{
		fTime -= InDeltaTime;
		if (0 >= fTime)
		{
			m_NoNickName->SetVisibility(ESlateVisibility::Hidden);
			fTime = 3.f;
			bTime = false;
		}
	}

	if (bLevel)
	{
		fMainLevelTime -= InDeltaTime;
		if (0 >= fMainLevelTime)
		{
			//���⼭ ��ŸƮ �����γѾ��
			StartOpenLevelTime();
			fMainLevelTime = 2.f;
			bLevel = false;
		}
	}

	UEServerConnect::GetInst().MainProcess.MsgUpdate();
}

//ĳ���ͻ�����ư(������ �����Ե�)
void UWidget_Select::MainCreateButtonCallback()
{
	//�ָ��������� �������������� ĳ���ͻ����ʿ� �ϳ� �����̾ ����� 
	// �̶�������ȵ�

	

	SelectCharacterPacket SelectPacket;
	//���̵�,����ٽú����ߵ�

	SelectPacket.ID = *UWidget_Start::IDText;
	SelectPacket.PASS = *UWidget_Start::PASSText;
	SelectPacket.NICKNAME = *m_NickName;
	//SelectPacket.CHARACTERNAME = 

	if (SelectPacket.NICKNAME == L"")
	{
		NotNickNameTime();
		return;
	}

	VisibleMainStart();
	MainCreateButton->SetVisibility(ESlateVisibility::Hidden);

	UHelMaGameInstance* GameInst = Cast<UHelMaGameInstance>(GetGameInstance());
	FString Str = GameInst->GetSelectPlayerName();
	SelectPacket.CHARACTERNAME = *Str;

	UEServerConnect::GetInst().Send(SelectPacket);




	//NewPacket.ID = *m_ID.ToString();
	//NewPacket.PASS = *m_Password.ToString();

	//IDText = m_ID.ToString();
	//PASSText = m_Password.ToString();


}

void UWidget_Select::GameStartCallback()
{
	
	HiddenMainStart();
	MainLevelImage->SetVisibility(ESlateVisibility::Visible);
	m_MainLevelText->SetVisibility(ESlateVisibility::Visible);
	bLevel = true;

	
}

void UWidget_Select::GameDelteCallback()
{
	DeleteCharacterPacket DeletePacket;

	DeletePacket.ID = *UWidget_Start::IDText;
	DeletePacket.PASS = *UWidget_Start::PASSText;
	DeletePacket.NICKNAME = *m_NickName;

	UEServerConnect::GetInst().Send(DeletePacket);

	VisibleMainStart();
}

void UWidget_Select::GameEndButtonCallback()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Start"));
}

void UWidget_Select::StartButtonEnable(bool bEnable)
{
	HiddenMainStart();
	StartButton->SetIsEnabled(bEnable);
	DeleteButton->SetIsEnabled(bEnable);
	MainCreateButton->SetIsEnabled(bEnable);
}

void UWidget_Select::BackButtonCallBack()
{
	VisibleMainStart();
	MainCreateButton->SetVisibility(ESlateVisibility::Hidden);

	SelectCharacterPacket SelectPacket;
	//���̵�,����ٽú����ߵ�

	SelectPacket.ID = *UWidget_Start::IDText;
	SelectPacket.PASS = *UWidget_Start::PASSText;

	//SelectPacket.CHARACTERNAME = 

	UHelMaGameInstance* GameInst = Cast<UHelMaGameInstance>(GetGameInstance());
	FString Str = GameInst->GetSelectPlayerName();
	SelectPacket.CHARACTERNAME = *Str;

	UEServerConnect::GetInst().Send(SelectPacket);
}


//�̹� �г����� ��������մٸ� �̾��̵� �װ��� �űԻ�����ư�� �Ⱥ��δ�
void UWidget_Select::CreateButtonCallback0()
{
	if (DataSize > 0)
	{
		//Data�����Ѵٴ°Ű� ���⿡�� CharactetUpdateData�� �ʿ���
		StartButton->SetIsEnabled(true);
		DeleteButton->SetIsEnabled(true);
		m_NickName = CreateString;
		return;
	}
	m_NickName = L"";
	HiddenMainStart();
	MainCreateButton->SetVisibility(ESlateVisibility::Visible);
}

void UWidget_Select::CreateButtonCallback1()
{
	if (DataSize >1)
	{
		StartButton->SetIsEnabled(true);
		DeleteButton->SetIsEnabled(true);
		m_NickName = CreateString1;
		
		return;
	}
	m_NickName = L"";
	HiddenMainStart();
	MainCreateButton->SetVisibility(ESlateVisibility::Visible);
}

void UWidget_Select::CreateButtonCallback2()
{

	if (DataSize > 2)
	{
		StartButton->SetIsEnabled(true);
		DeleteButton->SetIsEnabled(true);
		m_NickName = CreateString2;
		return;
	}
	m_NickName = L"";
	HiddenMainStart();
	MainCreateButton->SetVisibility(ESlateVisibility::Visible);
}

void UWidget_Select::CreateButtonCallback3()
{
	if (DataSize > 3)
	{
		StartButton->SetIsEnabled(true);
		DeleteButton->SetIsEnabled(true);
		m_NickName = CreateString3;
		return;
	}
	m_NickName = L"";
	HiddenMainStart();
	MainCreateButton->SetVisibility(ESlateVisibility::Visible);
}



void UWidget_Select::HiddenMainStart()
{
	StartButton->SetVisibility(ESlateVisibility::Hidden);
	DeleteButton->SetVisibility(ESlateVisibility::Hidden);
	BackButton->SetVisibility(ESlateVisibility::Visible);
	CreateButton0->SetVisibility(ESlateVisibility::Hidden);
	CreateButton1->SetVisibility(ESlateVisibility::Hidden);
	CreateButton2->SetVisibility(ESlateVisibility::Hidden);
	CreateButton3->SetVisibility(ESlateVisibility::Hidden);
	SelectMainImage->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget0->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget1->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget2->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget3->SetVisibility(ESlateVisibility::Hidden);
	TextBox->SetVisibility(ESlateVisibility::Visible);

	
}
void UWidget_Select::VisibleMainStart()
{
	StartButton->SetVisibility(ESlateVisibility::Visible);
	DeleteButton->SetVisibility(ESlateVisibility::Visible);
	BackButton->SetVisibility(ESlateVisibility::Hidden);
	CreateButton0->SetVisibility(ESlateVisibility::Visible);
	CreateButton1->SetVisibility(ESlateVisibility::Visible);
	CreateButton2->SetVisibility(ESlateVisibility::Visible);
	CreateButton3->SetVisibility(ESlateVisibility::Visible);
	SelectMainImage->SetVisibility(ESlateVisibility::Visible);
	
	
	
	TextBox->SetVisibility(ESlateVisibility::Hidden);

}

void UWidget_Select::VisibleCharacterWidgetImg0()
{
	LOG(L"VisibleCharacterWidgetImg0");
	CharacterImg_Widget0->SetVisibility(ESlateVisibility::Visible);
}


void UWidget_Select::VisibleCharacterWidgetImg1()
{

	CharacterImg_Widget1->SetVisibility(ESlateVisibility::Visible);
}


void UWidget_Select::VisibleCharacterWidgetImg2()
{

	CharacterImg_Widget2->SetVisibility(ESlateVisibility::Visible);
}


void UWidget_Select::VisibleCharacterWidgetImg3()
{

	CharacterImg_Widget3->SetVisibility(ESlateVisibility::Visible);
}


void UWidget_Select::HiddentCharacterWidgetImg()
{

	CreateString = L"NewCreate";
	CreateString1 = L"NewCreate";
	CreateString2 = L"NewCreate";
	CreateString3 = L"NewCreate";

	CharacterImg_Widget0->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget1->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget2->SetVisibility(ESlateVisibility::Hidden);
	CharacterImg_Widget3->SetVisibility(ESlateVisibility::Hidden);
}

void UWidget_Select::NotNickNameTime()
{
	bTime = true;
	m_NoNickName->SetVisibility(ESlateVisibility::Visible);
}

//����� �Ѿ���� ������ ���� �ű�
void UWidget_Select::StartOpenLevelTime()
{
	StartCharacterPacket StartPacket;
	//���̵�,����ٽú����ߵ�

	StartPacket.ID = *UWidget_Start::IDText;
	StartPacket.PASS = *UWidget_Start::PASSText;
	StartPacket.NICKNAME = *m_NickName;


	//CreateString

	UEServerConnect::GetInst().Send(StartPacket);

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}