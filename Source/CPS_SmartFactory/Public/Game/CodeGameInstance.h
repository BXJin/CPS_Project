// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * 
 */
class ACodeDataManager;

UCLASS()
class CPS_SMARTFACTORY_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	//TObjectPtr<ACodeDataManager> DataManager;

};
