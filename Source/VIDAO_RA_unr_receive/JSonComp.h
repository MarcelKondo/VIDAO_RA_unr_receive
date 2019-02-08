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
	

	UFUNCTION(BlueprintCallable, Category = "Json")
	const FVector GetJsonVectorField(const FString & JsonString, FString & FieldName);

	bool JsonStringToObject(
			const FString & JsonString,
			TSharedPtr<FJsonObject> & OutJsonObject
	);
	
protected:	
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
