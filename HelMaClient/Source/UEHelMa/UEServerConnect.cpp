// Fill out your copyright notice in the Description page of Project Settings.


#include "UEServerConnect.h"
#include <ClientToServer.h>
#include <GameEngineSerializer.h>
#include <ServerToClient.h>
#include <ServerToClientPacketUpdater.h>
#include "ClientPacketFunc.h"
#include "Widget_Start.h"


// int ConnectTesk::Check = 0;

void ConnectTask::DoWork()
{
    // ++Check;

    // �𸮾� �α״� �����忡 �����մϴ�.

    // �̳༮�� task�� ó���ϰ� ������ ���� task�� ó���ϴ� ������� �����ϴ� �������ε�.
    // while�� �ɾ������
    // �𸮾� �ɰ��� ������ ����ų���� �ֽ��ϴ�.
    // �� ��������� �ٸ� �α׳� �̷��༮���� ó���ϱ� ���ؼ� ������� �༮�̱� ������
    // ���� �ű⿡ ���� ������ �̴ϴ�.
    // �ѹ��� �ϳ��� �Լ��� ó���ϴ� �뵵�� �����忡��
    // ���� �װ� ������ �����ع����� �𸮾� �ɰ��� ������ ����ų���� �ֽ��ϴ�.
  
    UEServerConnect::GetInst().Connect();

    // �𸮾� �� ������Ǯ�� ���� ����ϱ� ������
    // ��������� ���⼭ while�� ����ϸ� �ȵ˴ϴ�.

}

void ConnectTask::DoWorkMain()
{
    DoWork();
}
/////////////////////////////////////////////////////// 

UnrealRecvThread::UnrealRecvThread()
{
    UEServerConnect::GetInst().m_ThreadProcess.Exchange(1);
}

//��� ���ư��°� Recv�޴°�
uint32 UnrealRecvThread::Run()
{
    UEServerConnect::GetInst().m_ThreadProcess.Exchange(1);

    // ��� �÷������� 
    // ���� �� �������� �ѹ� ���մٴ°� �����̹Ƿ� �������� ���� ������ ��� ���Ͽ��� �������� �ʰ� ���� Client
    FSocket* ConnectSocket = UEServerConnect::GetInst().ConnectSocket;


    int RecvByte = 0;

    uint8 ArrBuffer[1024 * 8];


    while (1 == UEServerConnect::GetInst().m_ThreadProcess)
    {
        // UE_LOG(LogTemp, Error, L"??");
        // Ŀ��Ʈ�� �߸��Ȱ��̴�.
        if (false == ConnectSocket->Recv(ArrBuffer, sizeof(ArrBuffer), RecvByte))
        {
            UE_LOG(LogTemp, Error, L"Recv Error false");
            break;
        }

        ServerToClientPacketUpdater Converter(reinterpret_cast<char*>(ArrBuffer), RecvByte);
        // ��Ŷ�� ��� ó���Ҷ����� ��� ����.
        while (false == Converter.IsEnd())
        {
            const char* Text = Converter.Update();
            FString Fs = FString(ANSI_TO_TCHAR(Text));
            if (Fs != TEXT("PlayerUpdatePacket"))
            {
                //��񸷾Ƴ� �ʹ����̿�
               // LOG(L"%s %d", *Fs, RecvByte);
            }
        }
    }

    UE_LOG(LogTemp, Error, L"Thread End");
    return 0;
}
void UnrealRecvThread::Stop()
{
    UEServerConnect::GetInst().m_ThreadProcess.Exchange(0);
}
void UnrealRecvThread::Exit()
{

}


////////////////////////////////////////////////////////////////////

UEServerConnect::UEServerConnect() : ConnectSocket(nullptr), m_IsConnect(false), RecvThread(NULL), IsServer(true)
{
  
}

UEServerConnect::~UEServerConnect()
{

}


UEServerConnect& UEServerConnect::GetInst()
{
    static UEServerConnect Inst;
    return Inst;
}

bool UEServerConnect::IsConnect()
{
    // ���⿡ ���̴� ������ ������ �������� ����?
    // �����忡�� ó���ɶ� ���⿡�� �˷��ִ� ������ ������ �ɼ��� �ִ�.

    return m_IsConnect;
}

void UEServerConnect::ConnectSocketCreate()
{
    // Ŀ��Ʈ�� �����忡�� ������ �Ǵµ�.
    Close();

    ISocketSubsystem* SSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

    if (nullptr == SSS)
    {
       LOG(L"if (nullptr == SSS)");
        return;
    }

    LOG(L"Socket Init");

    // FTcpSocketBuilder("SERVERGAMECONNECTER").AsReusable();


    // NAME_DGram UDP
    ConnectSocket = SSS->CreateSocket(NAME_Stream, "ServerGameConnecter", false);
    ConnectSocket->SetNoDelay(true);

    if (NULL != ConnectSocket)
    {
        LOGERROR(L"Socket Create OK");
    }
    else {
        LOGERROR(L"Socket Create ERROR");
    }

    FIPv4Address::Parse(UWidget_Start::IPText, ip);
    EndPoint = FIPv4Endpoint(ip, 30000);
    LOG(L"%s", *UWidget_Start::IPText);

    // ConnectSocket->Bind(EndPoint.ToInternetAddr().Get());
}

bool UEServerConnect::Connect()
{
    ConnectSocketCreate();

    // ������ �����带 ����� �׳� �α׶�� ���ڽ��ϴ�.

    //���� ��������� Connect�õ� �Ҷ� �����ʿ��� IOCP�� ���� Overlad���� Accept�� �����Ѵ�
    if (false == ConnectSocket->Connect(EndPoint.ToInternetAddr().Get()))
    {
        ISocketSubsystem* SSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        FString ErrorText = SSS->GetSocketError(SSS->GetLastErrorCode());
        LOGERROR(L"Server Error %s", *ErrorText);
        ConnectSocket = NULL;
        m_IsConnect = false;
        return false;
    }

    m_IsConnect = true;

    LOG(L"Server Connect Success");

    // ��� ���ټ� �־�� ��Ŷó���� ����������.
    // ClientPacketFunc::Init();

    // ���ú� ������� �̶� ���������.
    if (true == FPlatformProcess::SupportsMultithreading())
    {
        RecvThread = new UnrealRecvThread();
        RecvFRunnable = FRunnableThread::Create(RecvThread, TEXT("RecvThread"));
    }


    return true;
}

// ���ุ ���ָ� �����忡 �Ѱܼ� Ŀ��Ʈ�� ó���ϰ� �׿� ���� ���¸� �˷��ִ� �Լ�
void UEServerConnect::ConnectTaskStart()
{
    // �̶� �׳� �����带 �����ڽ��ϴ�.


    if (nullptr == ConnectTaskAsync)
    {
        ConnectTaskAsync = new FAutoDeleteAsyncTask<ConnectTask>();
    }

    ConnectTaskAsync->StartBackgroundTask()
        ;

    // ����ϴ� ���� �����忡 �ڽ��� �ѱ�� �ȴ�.
    // ConnectTaskAsync.StartBackgroundTask();
}

void UEServerConnect::ThreadStop()
{
    if (NULL != RecvThread)
    {
        RecvThread->Stop();
        RecvThread = NULL;
    }
}

void UEServerConnect::Close()
{
    LOG(L"UnServerConnect::Close() ");

    // SSS;
    m_Login.Exchange(0); // 0�̸� ���� �α����� ����� ���� �ʾҴ�.
    m_GameStart.Exchange(0); // �����

    //if (nullptr != SSS)
    //{
    //    SSS->ShutdownAllSystems();
    //}

    if (nullptr != ConnectTaskAsync)
    {
        ConnectTaskAsync = NULL;
    }

    if (nullptr != ConnectSocket)
    {
        ConnectSocket->Close();
        ConnectSocket = nullptr;
    }
}



// �־��ַ��� ����
void UEServerConnect::Send(const uint8* Data, int32 Count/*, int32& BytesSent*/)
{
    LOG(L"UESERVER::SEND");
    ConnectSocket->Send(Data, Count, m_SendByte);
}

void UEServerConnect::Send(ClientToServer& _Data)
{
    
    GameEngineSerializer Ser = _Data.Serialize();
    // UE_LOG(LogTemp, Error, TEXT("Pacekt %d %d"), _Data.GetCType(), Ser.GetOffsetInt());
    ConnectSocket->Send(Ser.GetUnsignedBuffer(), Ser.GetOffsetInt(), m_SendByte);
}

void UEServerConnect::Init(UWorld* _World)
{
    UEServerConnect::GetInst().m_CharacterData.ItemDatas.clear();
    MainProcess.MsgListInit(3, 1000);
    MainWorld = _World;
    m_ThreadProcess.Exchange(1);
    m_Login.Exchange(0); // 0�̸� ���� �α����� ����� ���� �ʾҴ�.
    m_GameStart.Exchange(0); // �����
    m_IsConnect = false;

    ClientPacketFunc::Init();
}