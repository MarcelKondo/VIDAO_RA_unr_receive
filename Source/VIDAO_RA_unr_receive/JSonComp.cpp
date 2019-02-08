// Fill out your copyright notice in the Description page of Project Settings.

#include "JSonComp.h"


// Sets default values for this component's properties
UJSonComp::UJSonComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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

bool UJSonComp::JsonStringToObject(
	const FString & JsonString,
	TSharedPtr<FJsonObject> &OutJsonObject
){
	TSharedRef< TJsonReader<> > Reader = TJsonReaderFactory<>::Create(JsonString);
	if (FJsonSerializer::Deserialize(Reader, OutJsonObject))
	{
		return true;
	}
	
	
	//FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &Struct, 0, 0);
	/*FJsonSerializer::Deserialize(Reader, JsonObject)*/
	return false;
}

const FVector UJSonComp::GetJsonVectorField(const FString & JsonString, FString & FieldName) {

	TSharedPtr<FJsonObject> JsonObject;
	JsonStringToObject(JsonString, JsonObject);
	TSharedPtr<FJsonObject> VectorObj = JsonObject->GetObjectField(FieldName);
	FVector Vector = FVector(VectorObj->GetNumberField("x"), VectorObj->GetNumberField("y"), VectorObj->GetNumberField("z"));

	return Vector;
}