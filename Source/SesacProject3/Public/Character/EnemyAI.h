// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyBase.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class SESACPROJECT3_API AEnemyAI : public AEnemyBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void EndAttack() override;
};