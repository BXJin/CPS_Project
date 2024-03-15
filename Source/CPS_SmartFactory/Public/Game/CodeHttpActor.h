// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "CodeHttpActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGetDataCompletedDelegate);

UCLASS()
class CPS_SMARTFACTORY_API ACodeHttpActor : public AActor
{
	GENERATED_BODY()
	
public:
	ACodeHttpActor();
	// ������ �Լ��� �ణ �����Ѵ�
	ACodeHttpActor(const class FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void SendHttpGet(); // http ��û�� ����� �Լ�

	// http GET ��û ���� ȣ��Ǵ� �ݹ��Լ�
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void SetURL(const FString& ChangeURL, bool IsObject);

 	TSharedPtr<FJsonObject> ReturnObjectData() const { return ObjectData; }

	TArray<TSharedPtr<FJsonValue>> ReturnArrayData() const { return ArrayData; }

	UPROPERTY(BlueprintAssignable)
	FGetDataCompletedDelegate OnDataCompletedCallback;

private:
	FHttpModule* Http;

	FString URL;

	TSharedPtr<FJsonObject> ObjectData;

	TArray<TSharedPtr<FJsonValue>> ArrayData;

	bool IsObjectType = true;
};
