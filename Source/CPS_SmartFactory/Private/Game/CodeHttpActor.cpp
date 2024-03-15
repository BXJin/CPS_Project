// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/CodeHttpActor.h"

ACodeHttpActor::ACodeHttpActor()
{
}

// Sets default values
ACodeHttpActor::ACodeHttpActor(const class FObjectInitializer& ObjectInitializer) 
{
	Http = &FHttpModule::Get();
}

void ACodeHttpActor::SendHttpGet()
{
	//Create the Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	// Bind response function to Request
	Request->OnProcessRequestComplete().BindUObject(this, &ACodeHttpActor::OnResponseReceived);
	// Setting the URL - where to send the request
	Request->SetURL(URL);
	// Adding What type of Request
	Request->SetVerb("GET");
	// Let Server know what application sent the request
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	// Let Request know what response we are expecting
	Request->SetHeader("Content-Type", TEXT("application/json"));
	// Sending the Request
	Request->ProcessRequest();
}

void ACodeHttpActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (IsObjectType)
	{
		// Create a JsonObject we will be working with
		TSharedPtr<FJsonObject> JsonObject;

		// Check if we are successful in our request
		if (Response->GetResponseCode() == 200)
		{
			//GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, TEXT("GetResponseCode"));

			// Store the response in our response body
			const FString ResponseBody = Response->GetContentAsString();
			// Creating a reader for the ResponseBody
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

			// Deserialize the json data given Reader and the actual object to deserialize
			// Check if we are successful in reading the json
			if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				ObjectData = JsonObject;
			}
		}
	}
	else
	{
		TArray<TSharedPtr<FJsonValue>> JsonArray;

		if (Response->GetResponseCode() == 200)
		{
			const FString ResponseBody = Response->GetContentAsString();
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

			if (FJsonSerializer::Deserialize(Reader, JsonArray))
			{
				ArrayData = JsonArray;
			}
		}
	}

	if (OnDataCompletedCallback.IsBound())
	{
		OnDataCompletedCallback.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("BroadCast!"));
	}
}

void ACodeHttpActor::SetURL(const FString& ChangeURL, bool IsObject)
{
	URL = ChangeURL;
	IsObjectType = IsObject;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("URL : %s"), *URL));

	SendHttpGet();
}

