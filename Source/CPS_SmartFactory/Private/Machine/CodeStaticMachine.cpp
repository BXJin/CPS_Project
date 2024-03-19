// Fill out your copyright notice in the Description page of Project Settings.


#include "Machine/CodeStaticMachine.h"
#include "Components/StaticMeshComponent.h"


ACodeStaticMachine::ACodeStaticMachine()
{
	StaticMachineMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMachine");
	StaticMachineMesh->SetupAttachment(RootComponent); 
	StaticMachineMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	IsStaticType = true;
}

void ACodeStaticMachine::BeginPlay()
{
	Super::BeginPlay();

}

void ACodeStaticMachine::SetHighLight()
{
	if (!IsValid(StaticMachineMesh))
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMesh"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *StaticMachineMesh->GetStaticMesh()->GetName()));
	if (IsHighLight)
	{
		StaticMachineMesh->SetRenderCustomDepth(false);
		IsHighLight = false;
	}
	else
	{
		StaticMachineMesh->SetRenderCustomDepth(true);
		IsHighLight = true;
	}
}

void ACodeStaticMachine::OnOutLine()
{
	if (!IsValid(StaticMachineMesh))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMesh"));
		return;
	}

	StaticMachineMesh->SetRenderCustomDepth(true);
	IsHighLight = true;
}

void ACodeStaticMachine::OffOutLine()
{
	if (!IsValid(StaticMachineMesh))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMesh"));
		return;
	}

	StaticMachineMesh->SetRenderCustomDepth(false);
	IsHighLight = false;
}
