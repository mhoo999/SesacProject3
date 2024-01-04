// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAI.h"

#include "MyGameStateBase.h"

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	Defence();
}

void AEnemyAI::Tick(float DeltaSeconds)
{
	if (GetWorld()->GetGameState<AMyGameStateBase>()->IsRoundStarted() == false) return;
	Super::Tick(DeltaSeconds);
	
	GazeAtTarget();

	switch (EnemyState)
	{
	case EEnemyState::ATTACK:
		PitchRotator.Pitch += DeltaSeconds * AttackSpeed;
		if (PitchRotator.Pitch <= AttackEndPitchRotation)
		{
			EndAttack();
		}
		break;
	case EEnemyState::DEFENCE:
		if (RotateHand(DeltaSeconds))
		{
			Attack();
		}
		else
		{
			float RollValue = RollRotator.Roll;
	
			if (RollValue > 180.f)
			{
				RollValue -= 360.f;
			}
			
			// MoveHorizontal(RollValue);
		}
		break;
	case EEnemyState::STUN:
		break;
	}
}

void AEnemyAI::Attack()
{
	Super::Attack();
	EnemyState = EEnemyState::ATTACK;
}

void AEnemyAI::Defence()
{
	Super::Defence();
	EnemyState = EEnemyState::DEFENCE;
}

void AEnemyAI::StartStun()
{
	Super::StartStun();

	EnemyState = EEnemyState::STUN;
}

void AEnemyAI::EndAttack()
{
	Super::EndAttack();
	
	TargetRollRotation = RollRotator.Roll + FMath::RandRange(-180.f, 180.f);

	if (TargetRollRotation < -180.f)
	{
		TargetRollRotation += 360.f;
	}

	if (TargetRollRotation > 180.f)
	{
		TargetRollRotation -= 360.f;
	}
	
	Defence();
}