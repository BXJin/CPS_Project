// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CodeGameMode.h"
#include "Machine/CodeBaseMachine.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CodeBaseCamera.h"

void ACodeGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACodeBaseMachine::StaticClass(), OutActor);

	//for (auto Value : OutActor)
	//{
	//	ACodeBaseMachine* BM = Cast<ACodeBaseMachine>(Value);
	//	if (IsValid(BM))
	//		WholeMachines.Add(BM);
	//}
	WholeMachines = reinterpret_cast<TArray<ACodeBaseMachine*>&>(OutActor);

	if (WholeMachines.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMachines"));
		return;
	}

	for (auto Value : WholeMachines)
	{
		if((Value->Tags).Num() != 0)
			TagsList.AddUnique(Value->Tags[0]);
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoTag"));

	}
}

void ACodeGameMode::SetDefault()
{
	ACodeBaseCamera* BaseCamera = Cast<ACodeBaseCamera>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (IsValid(BaseCamera))
	{
		BaseCamera->SetCameraRotDefault();
		BaseCamera->SetCameraLocation(FVector(0.0f, 0.0f, 0.0f));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoCamera"));
}

void ACodeGameMode::SetPawnLoacation(FVector TargetLocation)
{
	ACodeBaseCamera* BaseCamera = Cast<ACodeBaseCamera>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (IsValid(BaseCamera))
	{
		BaseCamera->SetCameraLocation(TargetLocation);
	}
}
