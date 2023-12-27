// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyBase.h"
#include "EnemyDummy.generated.h"

/**
 * 
 */
UCLASS()
class SESACPROJECT3_API AEnemyDummy : public AEnemyBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddHandRotaiton();
};