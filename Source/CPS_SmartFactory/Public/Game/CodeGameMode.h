// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodeGameMode.generated.h"

class ACodeBaseMachine;

UCLASS()
class CPS_SMARTFACTORY_API ACodeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Code")
	TArray<ACodeBaseMachine*> WholeMachines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	TArray<FName> TagsList;

public:
	UFUNCTION(BlueprintCallable)
	void SetDefault();

	UFUNCTION(BlueprintCallable)
	void SetPawnLoacation(FVector TargetLocation);
};
