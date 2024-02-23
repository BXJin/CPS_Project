// Fill out your copyright notice in the Description page of Project Settings.


#include "Machine/CodeBaseMachine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACodeBaseMachine::ACodeBaseMachine() : IsHighLight(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MachineMesh = CreateDefaultSubobject<UStaticMeshComponent>("Machine");
	MachineMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACodeBaseMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACodeBaseMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACodeBaseMachine::SetHighLight()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("SetHighLight"));
	if(!IsValid( MachineMesh))
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMesh"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *MachineMesh->GetStaticMesh()->GetName()));
	if (IsHighLight)
	{
		MachineMesh->SetRenderCustomDepth(false);
		IsHighLight = false;
	}
	else
	{
		MachineMesh->SetRenderCustomDepth(true);
		IsHighLight = true;
	}

}

