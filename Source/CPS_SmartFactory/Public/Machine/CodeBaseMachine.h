// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeBaseMachine.generated.h"

UCLASS()
class CPS_SMARTFACTORY_API ACodeBaseMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeBaseMachine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	bool IsHighLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	FVector WorldLocation = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	int32 MachineID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Code")
	bool IsStaticType;

public:
	UFUNCTION(BlueprintCallable)
	virtual void SetHighLight();

	UFUNCTION(BlueprintCallable)
	virtual void OnOutLine();

	UFUNCTION(BlueprintCallable)
	virtual void OffOutLine();

};
