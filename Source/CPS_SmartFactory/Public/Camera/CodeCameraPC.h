// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CodeCameraPC.generated.h"

/**
 * 
 */
class ACodeDataManager;

UCLASS()
class CPS_SMARTFACTORY_API ACodeCameraPC : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetDefault();

	UFUNCTION(BlueprintCallable)
	void SetPawnLoacation(FVector TargetLocation);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* MainWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	TObjectPtr<ACodeDataManager> DataManager;
};
