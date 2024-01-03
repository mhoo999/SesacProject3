// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "EnhancedInputComponent.h"
#include "WidgetComp.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SESACPROJECT3_API UWidgetComp : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWidgetComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent, UInputAction* input);
	class APlayerCharacter* Player;

	void MouseLeftClick(const FInputActionValue& value);
	void MouseLeftRelease(const FInputActionValue& value);
};
