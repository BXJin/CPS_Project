// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CodeBaseCamera.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACodeBaseCamera::ACodeBaseCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	RootSphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(RootSphereComponent);
	RootSphereComponent->SetCollisionProfileName(TEXT("NoCollision"));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootSphereComponent);
	CameraBoom->TargetArmLength = DefaultArmLength; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ACodeBaseCamera::BeginPlay()
{
	Super::BeginPlay();

	Controller->SetControlRotation(DefaultRotator);
	SetActorLocation(FVector(0.0f, 0.0f, 10.0f));
}

void ACodeBaseCamera::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		//FRotator ControlRotation = Controller->GetControlRotation();
		//GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Blue, FString::Printf(TEXT("Yaw: %f, Pitch: %f"), 
		//	ControlRotation.Yaw, ControlRotation.Pitch));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("NoController"));
	}
}

void ACodeBaseCamera::Zoom(const FInputActionValue& Value)
{
	float ZoomAxis = -1.0f * Value.Get<float>();

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Zooming"));

	if (Controller != nullptr)
	{
		const float NewTargetArmLenght = CameraBoom->TargetArmLength + ZoomAxis * ZoomStep;
		CameraBoom->TargetArmLength = FMath::Clamp(NewTargetArmLenght, MinZoomLeght, MaxZoomLeght);
	}
}


void ACodeBaseCamera::SetCameraRotDefault()
{
	FTimerHandle TimerHandle;
	bool ShouldMove = true;
	float ErrorRange = 0.3f;

	//현재 카메라의 회전
	FRotator CurrentRotation = Controller->GetControlRotation();
	// 목표 회전
	FRotator TargetRotation = DefaultRotator;


	if (((CurrentRotation.Yaw <= TargetRotation.Yaw + ErrorRange)) && (CurrentRotation.Yaw >= TargetRotation.Yaw - ErrorRange))
	{
		if (((CurrentRotation.Pitch <= TargetRotation.Pitch + ErrorRange)) && (CurrentRotation.Pitch >= TargetRotation.Pitch - ErrorRange))
		{
			Controller->SetControlRotation(TargetRotation);
			ShouldMove = false;
		}
	}

	if (ShouldMove)
	{
		float InterpSpeed = 5.0f;
		float TimerRate = 0.01f;

		// 보간된 회전값 계산 (선형 보간 사용)
		FRotator InterpolatedRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), InterpSpeed);
		// 컨트롤러에 보간된 회전값 설정
		Controller->SetControlRotation(InterpolatedRotation);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACodeBaseCamera::SetCameraRotDefault, TimerRate, false);
	}

}

void ACodeBaseCamera::SetCameraLocation(FVector ActorLocation)
{
	TargetLocation = ActorLocation;
	SetLocationTimerFunction();
}

void ACodeBaseCamera::SetLocationTimerFunction()
{
	FTimerHandle TimerHandle;
	bool ShouldMove = true;
	float ErrorRange = 5.0f;

	FVector CurrentLocation = GetActorLocation();

	if ((CurrentLocation.X <= TargetLocation.X + ErrorRange) && (CurrentLocation.X >= TargetLocation.X - ErrorRange))
		if ((CurrentLocation.X <= TargetLocation.X + ErrorRange) && (CurrentLocation.X >= TargetLocation.X - ErrorRange))
		{
			SetActorLocation(TargetLocation);
			GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Blue, FString::Printf(TEXT("X: %f, Y: %f"),
				CurrentLocation.X, CurrentLocation.Y));
			ShouldMove = false;
		}

	if (ShouldMove)
	{
		float InterpSpeed = 5.0f;
		float TimerRate = 0.01f;
		// 보간된 위치값 계산 (선형 보간 사용)
		FVector InterpolatedLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), InterpSpeed);
		// 카메라에 보간된 위치값 설정
		SetActorLocation(InterpolatedLocation);

		//GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Blue, FString::Printf(TEXT("X: %f, Y: %f"),
		//	CurrentLocation.X, CurrentLocation.Y));

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACodeBaseCamera::SetLocationTimerFunction, TimerRate, false);
	}
}

// Called every frame
void ACodeBaseCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACodeBaseCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedPlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (EnhancedPlayerInputComponent == nullptr || PlayerController == nullptr)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

	if (EnhancedSubsystem == nullptr)
	{
		return;
	}

	EnhancedSubsystem->AddMappingContext(DefaultMappingContext, 1);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACodeBaseCamera::Look);

		// Zooming
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ACodeBaseCamera::Zoom);

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("BindCompleted"));
	}
}

