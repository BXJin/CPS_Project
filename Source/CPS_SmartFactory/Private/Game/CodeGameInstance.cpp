// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CodeGameInstance.h"
#include "Game/CodeDataManager.h"

void UCodeGameInstance::Init()
{
	Super::Init();

	//DataManager = GetWorld()->SpawnActor<ACodeDataManager>(ACodeDataManager::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
}
