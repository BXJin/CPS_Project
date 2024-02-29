// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeBaseMachine.generated.h"

class UStaticMeshComponent;

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
	UStaticMeshComponent* MachineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	bool IsHighLight;

public:
	UFUNCTION(BlueprintCallable)
	void SetHighLight();

	UFUNCTION(BlueprintCallable)
	void OnOutLine();

	UFUNCTION(BlueprintCallable)
	void OffOutLine();

};
