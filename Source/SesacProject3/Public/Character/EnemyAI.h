// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyBase.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UENUM()
enum class EEnemyState : uint8
{
	NONE,
	ATTACK,
	DEFENCE,
	STUN,
	SIZE
};

UCLASS()
class SESACPROJECT3_API AEnemyAI : public AEnemyBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void Attack() override;
	virtual void Defence() override;

	virtual void StartStun() override;

protected:
	virtual void EndAttack() override;

	UPROPERTY(EditAnywhere)
	EEnemyState EnemyState;
};