// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CodeCameraPC.h"
#include "Camera/CodeBaseCamera.h"
#include "Blueprint/UserWidget.h"
#include "Game/CodeDataManager.h"

void ACodeCameraPC::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	MainWidget->AddToViewport();
	SetShowMouseCursor(true);
	SetInputMode(FInputModeGameAndUI());

	DataManager = GetWorld()->SpawnActor<ACodeDataManager>(ACodeDataManager::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
}

void ACodeCameraPC::SetDefault()
{
	ACodeBaseCamera* BaseCamera = Cast<ACodeBaseCamera>(GetPawn());
	if (IsValid(BaseCamera))
	{
		BaseCamera->SetCameraRotDefault();
		BaseCamera->SetCameraLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoCamera"));
}

void ACodeCameraPC::SetPawnLoacation(FVector TargetLocation)
{
	ACodeBaseCamera* BaseCamera = Cast<ACodeBaseCamera>(GetPawn());
	if (IsValid(BaseCamera))
	{
		BaseCamera->SetCameraLocation(TargetLocation);
	}
}
