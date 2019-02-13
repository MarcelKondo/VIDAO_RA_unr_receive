// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "JSonComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VIDAO_RA_UNR_RECEIVE_API UJSonComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJSonComp();
	

	UFUNCTION(BlueprintPure, Category = "Json")
		const FVector GetJsonVectorField(FString JsonString, FString FieldName);
		
	UFUNCTION(BlueprintPure, Category = "Json")
		const FQuat GetJsonQuatField(FString JsonString, FString FieldName);

	UFUNCTION(BlueprintPure, Category = "Json")
		const FRotator GetJsonRotatorField(FString JsonString, FString FieldName);

	UFUNCTION(BlueprintPure, Category = "Json")
		int GetJsonIntField(FString JsonString, FString FieldName);

	UFUNCTION(BlueprintPure, Category = "Json")
		const FString GetJsonStringField(FString JsonString, FString FieldName);

	UFUNCTION(BlueprintCallable, Category = "Json")
		void JsonStringToPosRot(FString JsonString, FVector & Location, FRotator & Rotator);
	
protected:	
	bool JsonStringToObject(
		const FString & JsonString,
		TSharedPtr<FJsonObject> & OutJsonObject
	);

	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
