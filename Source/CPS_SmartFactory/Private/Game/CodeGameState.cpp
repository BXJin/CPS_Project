// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CodeGameState.h"
#include "Machine/CodeBaseMachine.h"
#include "Kismet/GameplayStatics.h"

void ACodeGameState::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACodeBaseMachine::StaticClass(), OutActor);
	WholeMachines = reinterpret_cast<TArray<ACodeBaseMachine*>&>(OutActor);

	if (WholeMachines.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMachines"));
		return;
	}

	for (auto Value : WholeMachines)
	{
		if ((Value->Tags).Num() != 0)
			TagsList.AddUnique(Value->Tags[0]);
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoTag"));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), TagsList.Num()));
}
