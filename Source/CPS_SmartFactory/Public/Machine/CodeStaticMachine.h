// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine/CodeBaseMachine.h"
#include "CodeStaticMachine.generated.h"

class UStaticMeshComponent;

UCLASS()
class CPS_SMARTFACTORY_API ACodeStaticMachine : public ACodeBaseMachine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	UStaticMeshComponent* StaticMachineMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ACodeStaticMachine();

public:
	virtual void SetHighLight() override;

	virtual void OnOutLine() override;

	virtual void OffOutLine() override;
};
