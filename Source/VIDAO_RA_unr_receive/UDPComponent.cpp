// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPComponent.h"



// Called every frame
void UUDPComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UUDPComponent::UUDPComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ListenSocket = NULL;
	//Socket = new FSocket(SOCKTYPE_Datagram);

}

// Called when the game starts or when spawned
void UUDPComponent::BeginPlay()
{
	Super::BeginPlay();
	StartUDPReceiver("", "0.0.0.0", port);
}


bool UUDPComponent::StartUDPReceiver(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort) {
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
	UDPReceiver->OnDataReceived().BindUObject(this, &UUDPComponent::Recv);
	UDPReceiver->Start();

	return true;
}

FString UUDPComponent::BytesToStringFixed(const uint8 *In, int32 Count)
{
	FString Broken = BytesToString(In, Count);
	FString Fixed;

	for (int i = 0; i < Broken.Len(); i++)
	{
		const TCHAR c = Broken[i] - 1;
		Fixed.AppendChar(c);
	}

	return Fixed;
}


void UUDPComponent::Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt)
{
	UE_LOG(LogTemp, Warning, TEXT("Received bytes"))
		//ScreenMsg("Received bytes", ArrayReaderPtr->Num());

		TArray<uint8> Data;
	Data.AddUninitialized(ArrayReaderPtr->TotalSize());
	ArrayReaderPtr->Serialize(Data.GetData(), ArrayReaderPtr->TotalSize());
	//*ArrayReaderPtr << Data;		//Now de-serializing! See AnyCustomData.h

	//BP Event
	
	OnDataReceived.Broadcast(Data, BytesToStringFixed(Data.GetData(), ArrayReaderPtr->TotalSize()));
	
}



void UUDPComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
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

