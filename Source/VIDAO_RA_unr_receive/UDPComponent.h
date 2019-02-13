// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Networking.h"
#include "SocketSubsystem.h"
#include "UDPComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) , Blueprintable)
class VIDAO_RA_UNR_RECEIVE_API UUDPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUDPComponent();

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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDataReceived, const TArray<uint8>&, AsBytes, const FString&, AsString);
	
	
	UPROPERTY(BlueprintAssignable, Category = "UDP")
		FOnDataReceived OnDataReceived;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FString BytesToStringFixed(const uint8 *In, int32 Count);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

		
	
};
