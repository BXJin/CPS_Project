// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Machine/CodeBaseMachine.h"
#include "CodeSkeletalMesh.generated.h"

class USkeletalMeshComponent;

UCLASS()
class CPS_SMARTFACTORY_API ACodeSkeletalMesh : public ACodeBaseMachine
{
	GENERATED_BODY()

public:
	ACodeSkeletalMesh();

public:
	virtual void SetHighLight() override;

	virtual void OnOutLine() override;

	virtual void OffOutLine() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	USkeletalMeshComponent* SkeletalMeshComponent;
};
