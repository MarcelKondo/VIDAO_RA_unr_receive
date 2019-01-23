// Fill out your copyright notice in the Description page of Project Settings.

#include "JSonComp.h"


// Sets default values for this component's properties
UJSonComp::UJSonComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJSonComp::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJSonComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UJSonComp::JsonStringToStruct(
	const FString & JsonString,
	const UStruct * Struct
){
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JsonString);
	//FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &Struct, 0, 0);
	/*FJsonSerializer::Deserialize(Reader, JsonObject)*/
	return true;
}