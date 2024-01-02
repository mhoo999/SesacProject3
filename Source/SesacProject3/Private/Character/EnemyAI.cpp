// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyAI.h"

#include "Weapon/WeaponBase.h"

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	Defence();
}

void AEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// 방어 중인 경우 (방어를 몇초 하다가 공격으로 전환할 것인지 체크)
	if (bIsDefence)
	{
		// 플레이어의 각도를 따라갈 것인지?
		// 일정 각도로 돌아갈 것인지?

		if (RotateHand(DeltaSeconds))
		{
			Attack();
		}
		
		MoveHorizontal(RollRotator.Roll);
	}
}

void AEnemyAI::EndAttack()
{
	Super::EndAttack();

	TargetRollRotation = FMath::RandRange(0.0f, 359.0f);
	
	Defence();
}