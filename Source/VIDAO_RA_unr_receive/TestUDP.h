// Fill out your copyright notice in the Description page of Project Settings.
// Based on Rama's RamaUDPReceiver
// Edited by MKondo


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "TestUDP.generated.h"

UCLASS()
class VIDAO_RA_UNR_RECEIVE_API ATestUDP : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestUDP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FString BytesToStringFixed(const uint8 *In, int32 Count);


public:
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UDP)
		int port = 55555;

	FSocket* ListenSocket;
	FUdpSocketReceiver* UDPReceiver = nullptr;

	bool StartUDPReceiver(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort
	);

	void Recv(const FArrayReaderPtr& ArrayReaderPtr, const FIPv4Endpoint& EndPt);

	UFUNCTION(BlueprintImplementableEvent)
		void OnDataReceived(const TArray<uint8>& AsBytes, const FString& AsString);


	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
