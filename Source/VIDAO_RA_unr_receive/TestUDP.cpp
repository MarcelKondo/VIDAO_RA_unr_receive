// Fill out your copyright notice in the Description page of Project Settings.

#include "TestUDP.h"




// Sets default values
ATestUDP::ATestUDP()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ListenSocket = NULL;
	PrimaryActorTick.bCanEverTick = true;
	//Socket = new FSocket(SOCKTYPE_Datagram);

}

// Called when the game starts or when spawned
void ATestUDP::BeginPlay()
{
	Super::BeginPlay();
	StartUDPReceiver("", "0.0.0.0", 55555);
}

// Called every frame
void ATestUDP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool ATestUDP::StartUDPReceiver(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort) {
	UE_LOG(LogTemp, Warning, TEXT("Starting UDP Receiver"))

		//~~~

		FIPv4Address Addr;
	FIPv4Address::Parse(TheIP, Addr);

	//Create Socket
	FIPv4Endpoint Endpoint(Addr, ThePort);

	//BUFFER SIZE
	int32 BufferSize = 2 * 1024 * 1024;

	ListenSocket = FUdpSocketBuilder(*YourChosenSocketName)
		.AsNonBlocking()
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.WithReceiveBufferSize(BufferSize);
	;

	check(ListenSocket != nullptr)

	FTimespan ThreadWaitTime = FTimespan::FromMilliseconds(100);
	UDPReceiver = new FUdpSocketReceiver(ListenSocket, ThreadWaitTime, TEXT("UDP Receiver"));
	UDPReceiver->OnDataReceived().BindUObject(this, &ATestUDP::Recv);
	UDPReceiver->Start();

	return true;
}

void ATestUDP::Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt)
{
	UE_LOG(LogTemp, Warning, TEXT("Received bytes"))
		//ScreenMsg("Received bytes", ArrayReaderPtr->Num());

	FString Data;
	*ArrayReaderPtr << Data;		//Now de-serializing! See AnyCustomData.h

	//BP Event
	BPEvent_DataReceived(Data);
}


void ATestUDP::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//~~~~~~~~~~~~~~~~
	UDPReceiver->Stop();
	delete UDPReceiver;
	UDPReceiver = nullptr;

	//Clear all sockets!
	//		makes sure repeat plays in Editor dont hold on to old sockets!
	if (ListenSocket)
	{
		ListenSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ListenSocket);
	}
}
