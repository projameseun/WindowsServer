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

    // 언리얼 로그는 쓰레드에 안전합니다.

    // 이녀석은 task를 처리하고 빠르게 다음 task를 처리하는 방식으로 동작하는 쓰레드인데.
    // while을 걸어버리면
    // 언리얼에 심각한 문제를 일으킬수가 있습니다.
    // 이 쓰레드들은 다른 로그나 이런녀석들을 처리하기 위해서 만들어진 녀석이기 때문에
    // 내가 거기에 같이 껴들어가는 겁니다.
    // 한번에 하나의 함수를 처리하는 용도의 쓰레드에서
    // 내가 그걸 완전히 점유해버리면 언리얼에 심각한 문제를 일으킬수가 있습니다.
  
    UEServerConnect::GetInst().Connect();

    // 언리얼도 이 쓰레드풀을 같이 사용하기 때문에
    // 저어어어얼대로 여기서 while을 사용하면 안됩니다.

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

//계속 돌아가는곳 Recv받는곳
uint32 UnrealRecvThread::Run()
{
    UEServerConnect::GetInst().m_ThreadProcess.Exchange(1);

    // 모든 플랫폼에서 
    // 내가 내 형식으로 한번 감쌌다는게 문제이므로 선생님이 만든 소켓은 모든 소켓에서 동작하지 않게 만든 Client
    FSocket* ConnectSocket = UEServerConnect::GetInst().ConnectSocket;


    int RecvByte = 0;

    uint8 ArrBuffer[1024 * 8];


    while (1 == UEServerConnect::GetInst().m_ThreadProcess)
    {
        // UE_LOG(LogTemp, Error, L"??");
        // 커넥트가 잘못된것이다.
        if (false == ConnectSocket->Recv(ArrBuffer, sizeof(ArrBuffer), RecvByte))
        {
            UE_LOG(LogTemp, Error, L"Recv Error false");
            break;
        }

        ServerToClientPacketUpdater Converter(reinterpret_cast<char*>(ArrBuffer), RecvByte);
        // 패킷을 모두 처리할때까지 계속 돈다.
        while (false == Converter.IsEnd())
        {
            const char* Text = Converter.Update();
            FString Fs = FString(ANSI_TO_TCHAR(Text));
            if (Fs != TEXT("PlayerUpdatePacket"))
            {
                //잠깐막아놈 너무많이옴
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
    // 여기에 쓰이는 변수는 문제가 터질수가 있죠?
    // 쓰레드에서 처리될때 여기에서 알려주는 변수가 문제가 될수가 있다.

    return m_IsConnect;
}

void UEServerConnect::ConnectSocketCreate()
{
    // 커넥트만 쓰레드에서 돌리면 되는데.
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

    // 무조건 쓰레드를 만들고 그냥 로그라고 찍어보겠습니다.

    //소켓 만들어지고 Connect시도 할때 서버쪽에서 IOCP에 감시 Overlad에서 Accept를 감지한다
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

    // 요걸 해줄수 있어야 패킷처리가 가능해진다.
    // ClientPacketFunc::Init();

    // 리시브 쓰레드는 이때 만들어진다.
    if (true == FPlatformProcess::SupportsMultithreading())
    {
        RecvThread = new UnrealRecvThread();
        RecvFRunnable = FRunnableThread::Create(RecvThread, TEXT("RecvThread"));
    }


    return true;
}

// 실행만 해주면 쓰레드에 넘겨서 커넥트를 처리하고 그에 대한 상태를 알려주는 함수
void UEServerConnect::ConnectTaskStart()
{
    // 이때 그냥 쓰레드를 만들어보겠습니다.


    if (nullptr == ConnectTaskAsync)
    {
        ConnectTaskAsync = new FAutoDeleteAsyncTask<ConnectTask>();
    }

    ConnectTaskAsync->StartBackgroundTask()
        ;

    // 사용하는 순간 쓰레드에 자신을 넘기게 된다.
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
    m_Login.Exchange(0); // 0이면 아직 로그인이 제대로 되지 않았다.
    m_GameStart.Exchange(0); // 여기ㅓ

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



// 넣어주려는 버퍼
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
    m_Login.Exchange(0); // 0이면 아직 로그인이 제대로 되지 않았다.
    m_GameStart.Exchange(0); // 여기ㅓ
    m_IsConnect = false;

    ClientPacketFunc::Init();
}