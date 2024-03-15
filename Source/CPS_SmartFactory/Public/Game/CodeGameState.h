// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CodeGameState.generated.h"

class ACodeBaseMachine;

UCLASS()
class CPS_SMARTFACTORY_API ACodeGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	TArray<ACodeBaseMachine*> WholeMachines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	TArray<FName> TagsList;

};
