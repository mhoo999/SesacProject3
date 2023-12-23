// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

AEnemyBase::AEnemyBase()
{
	RightHandMesh->SetupAttachment(RootComponent);
	LeftHandMesh->SetupAttachment(RootComponent);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	RightHandMesh->SetRelativeLocation(HandZeroLocation + FVector(0, 0, AttackDistance));
}

bool AEnemyBase::IsAttack()
{
	return bIsAttack;
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 손을 공격 방향으로 움직임
	if (bIsAttack)
	{
		RightHandMesh->AddWorldOffset(AttackDirection * AttackSpeed * DeltaSeconds);

		if ((RightHandMesh->GetRelativeLocation() - HandZeroLocation).Length() >= AttackDistance)
		{
			EndAttack();
		}
	}
	else
	{
		Attack();
	}
}

void AEnemyBase::Attack()
{
	bIsAttack = true;
	
	AttackDirection = HandZeroLocation - RightHandMesh->GetRelativeLocation();
	AttackDirection.Normalize();

	// Todo : 베쉬 이펙트 켜주기
}

void AEnemyBase::EndAttack()
{
	bIsAttack = false;

	// Todo : 베쉬 이펙트 꺼주기
}

void AEnemyBase::RotateHand()
{
	
}