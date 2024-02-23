// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CodePopupWidget.h"

void UCodePopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentState = PopupState::Default;
}

void UCodePopupWidget::SetPopupState(PopupState NewState)
{
	CurrentState = NewState;
}
