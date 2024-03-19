// Fill out your copyright notice in the Description page of Project Settings.


#include "Machine/CodeBaseMachine.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACodeBaseMachine::ACodeBaseMachine() : IsHighLight(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
}

void ACodeBaseMachine::OnOutLine()
{
}

void ACodeBaseMachine::OffOutLine()
{
}
