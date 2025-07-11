// Fill out your copyright notice in the Description page of Project Settings.


#include "SpartaPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h" // FInputActionValue를 위해 포함합니다.

// Sets default values
ASpartaPawn::ASpartaPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	// 이동 및 회전 속도 기본값 설정
	MoveSpeed = 1000.0f;
	RotationSpeed = 100.0f;
}

// Called when the game starts or when spawned
void ASpartaPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpartaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!MoveInputValue.IsZero())
	{
		FVector ForwardMovement = GetActorRightVector() * MoveInputValue.Y * MoveSpeed * DeltaTime;
		AddActorLocalOffset(ForwardMovement, true);

		FVector RightMovement = GetActorForwardVector() * MoveInputValue.X * MoveSpeed * DeltaTime;
		AddActorLocalOffset(RightMovement, true);
	}

	if (!LookInputValue.IsZero())
	{
		AddControllerYawInput(LookInputValue.X * RotationSpeed * DeltaTime);
		AddControllerPitchInput(LookInputValue.Y * RotationSpeed * DeltaTime);
		
		LookInputValue = FVector2D::ZeroVector; 
	}
}


void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* SpartaController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (SpartaController->MoveAction)
			{
				EnhancedInputComponent->BindAction(SpartaController->MoveAction, ETriggerEvent::Triggered, this, &ASpartaPawn::Move);
				EnhancedInputComponent->BindAction(SpartaController->MoveAction, ETriggerEvent::Completed, this, &ASpartaPawn::MoveComplete);
			}

			if (SpartaController->LookAction)
			{
				EnhancedInputComponent->BindAction(SpartaController->LookAction, ETriggerEvent::Triggered, this, &ASpartaPawn::Look);
			}
		}
	}
}



void ASpartaPawn::Move(const FInputActionValue& Value)
{
	MoveInputValue = Value.Get<FVector2D>();
}

void ASpartaPawn::Look(const FInputActionValue& Value)
{
	LookInputValue = Value.Get<FVector2D>();
}

void ASpartaPawn::MoveComplete(const FInputActionValue& Value)
{
	MoveInputValue = FVector2D::ZeroVector;
}
