// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CodeBaseCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USphereComponent;
struct FInputActionValue;

UCLASS()
class CPS_SMARTFACTORY_API ACodeBaseCamera : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Zoom Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

public:
	// Sets default values for this pawn's properties
	ACodeBaseCamera();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	USphereComponent* RootSphereComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	float MinZoomLeght = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	float MaxZoomLeght = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	float DefaultArmLength = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	float ZoomStep = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code")
	FRotator DefaultRotator = FRotator(-30.0f, 0.0f, 0.0f);

	FVector TargetLocation = FVector(0.0f,0.0f,0.0f);

protected:
	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for Zoom input */
	void Zoom(const FInputActionValue& Value);

	void SetLocationTimerFunction();
	
public:
	UFUNCTION(BlueprintCallable)
	void SetCameraRotDefault();

	UFUNCTION(BlueprintCallable)
	void SetCameraLocation(FVector ActorLocation);
};
