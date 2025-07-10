// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;


/**
 * 
 */
UCLASS()
class ASSIGNMENT_7_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASpartaPlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;
	
	virtual void BeginPlay() override;
	
};
