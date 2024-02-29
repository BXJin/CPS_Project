// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodePopupWidget.generated.h"

UENUM(BlueprintType)
enum class PopupState : uint8
{
    Default,
    Warning,
    Closed,
    // Add more states as needed
};

class UButton;
class UTextBlock;

UCLASS()
class CPS_SMARTFACTORY_API UCodePopupWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetPopup(PopupState NewState,const FText& Message);

	void SetPopup_Implementation(PopupState NewState, const FText& Message);

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Code")
    PopupState CurrentState;
};
