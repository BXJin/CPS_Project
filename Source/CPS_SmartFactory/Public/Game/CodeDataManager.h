// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeDataManager.generated.h"

UENUM(BlueprintType)
enum class EData :uint8
{
	ED_Main				UMETA(DisplayName = "Main"),
	ED_MachineData		UMETA(DisplayName = "MachineData"),
	ED_ResultData		UMETA(DisplayName = "ResultData"),
	ED_AlarmListData	UMETA(DisplayName = "AlarmListData"),
	ED_ResultChartData	UMETA(DisplayName = "ResultChartData"),
	ED_ResultIdxData	UMETA(DisplayName = "ResultIdxData"),
	ED_ASensor			UMETA(DisplayName = "ASensor"),
	ED_AAlarm			UMETA(DisplayName = "AAlarm"),
};

USTRUCT(BlueprintType)
struct FMachineDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	int32 Depth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	int32 NodeId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	int32 ParentId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	FString NodeName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	int32 Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	bool HasChild;
};

USTRUCT(BlueprintType)
struct FInnerMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	TMap<FString, FString> InnerMap;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FReturnMainValueDelegate);

class ACodeHttpActor;

UCLASS()
class CPS_SMARTFACTORY_API ACodeDataManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeDataManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetCurDataTypeAndURL(EData CurDataType, const FString& Param1 = "", const FString& Param2 = "", const FString& Param3 = "", const FString& Param4 = "");

	UFUNCTION(BlueprintCallable)
	void GetMainData();

	void SetTimerUpdateMainData();

	UFUNCTION(BlueprintCallable)
	FString ReturnMainDataValue(const FString& VcNameToAccess, const FString& DataNameToAccess);

	UFUNCTION(BlueprintCallable)
	void GetMachineData();

private:
	void PushMachineDataStruct(TArray<TSharedPtr<FJsonValue>> data);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	TMap<FString, FInnerMap> StoredMainDataMap;

	UPROPERTY(BlueprintAssignable)
	FReturnMainValueDelegate OnMainDataValueCallBack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	TArray<FMachineDataStruct> StoredMachineDataArray;
	
private:

	FString DataURL;

	TObjectPtr<ACodeHttpActor> MainHttpActor;

	TObjectPtr<ACodeHttpActor> MachineHttpActor;

	int32 StructIndex;

	int32 StructDepth;
};
