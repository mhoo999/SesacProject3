// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UENUM()
enum class EGameMode : uint8
{
	NONE,
	SINGLE,
	MULTI,
	SIZE,
};

UCLASS()
class SESACPROJECT3_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetGameMode(EGameMode NewGameMode);
	EGameMode GetGameMode() const;
private:
	UPROPERTY(Meta = (AllowPrivateAccess))
	EGameMode GameMode;
};