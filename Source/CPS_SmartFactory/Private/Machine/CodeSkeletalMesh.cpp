// Fill out your copyright notice in the Description page of Project Settings.


#include "Machine/CodeSkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"

ACodeSkeletalMesh::ACodeSkeletalMesh()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	IsStaticType = false;
}

void ACodeSkeletalMesh::SetHighLight()
{
	if (!IsValid(SkeletalMeshComponent))
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMesh"));
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *SkeletalMeshComponent->GetSkeletalMeshAsset()->GetName()));
	if (IsHighLight)
	{
		SkeletalMeshComponent->SetRenderCustomDepth(false);
		IsHighLight = false;
	}
	else
	{
		SkeletalMeshComponent->SetRenderCustomDepth(true);
		IsHighLight = true;
	}
}

void ACodeSkeletalMesh::OnOutLine()
{
	if (!IsValid(SkeletalMeshComponent))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMesh"));
		return;
	}

	SkeletalMeshComponent->SetRenderCustomDepth(true);
	IsHighLight = true;
}

void ACodeSkeletalMesh::OffOutLine()
{
	if (!IsValid(SkeletalMeshComponent))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoMesh"));
		return;
	}

	SkeletalMeshComponent->SetRenderCustomDepth(false);
	IsHighLight = false;
}
