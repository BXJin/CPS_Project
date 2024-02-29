// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CodePopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCodePopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentState = PopupState::Default;


}

void UCodePopupWidget::SetPopup_Implementation(PopupState NewState, const FText& Message)
{
}

