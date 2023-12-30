// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "VRPlayerAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class SESACPROJECT3_API UVRPlayerAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector LeftHandLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator LeftHandRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector RightHandLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator RightHandRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector HeadLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator HeadRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector LeftFootLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator LeftFootRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FVector RightFootLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly ,Category = MySettings)
	FRotator RightFootRotation;
};
