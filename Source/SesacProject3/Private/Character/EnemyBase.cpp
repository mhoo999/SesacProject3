// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

#include "Weapon/WeaponBase.h"

#include <Kismet/KismetMathLibrary.h>

AEnemyBase::AEnemyBase()
{
	HandZeroPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HandZeroPoint"));
	HandZeroPoint->SetupAttachment(RootComponent);
	RightHandMesh->SetupAttachment(HandZeroPoint);
	LeftHandMesh->SetupAttachment(HandZeroPoint);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	//RightHandMesh->SetRelativeLocation(HandZeroLocation + FVector(0, 0, AttackDistance));

	// Spawn Sword
	TestWeapon = GetWorld()->SpawnActor<AWeaponBase>();

	TestWeapon->AttachToComponent(RightHandMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	TestWeapon->SetActorRelativeLocation(FVector(33, 21, -3));
	TestWeapon->SetActorRelativeRotation(FRotator(0, 20, 0));
	TestWeapon->SetOwningPlayer(this);
}

bool AEnemyBase::IsAttack()
{
	return bIsAttack;
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Roll Rotation 회전은 Attack 과는 별개로 처리해야할듯 (Defence에서도 사용하므로)

	HandZeroPoint->SetRelativeRotation(FTransform(RollRotator).TransformRotation(PitchRotator.Quaternion()));

	// 방어 중인 경우
	if (bIsDefence)
	{
		
	}
	// 공격 중인 경우
	else if (bIsAttack)
	{
		//HandZeroPoint->AddLocalRotation(FRotator(AttackSpeed * DeltaSeconds,0,0));

		PitchRotator.Pitch += DeltaSeconds * AttackSpeed;

		if (PitchRotator.Pitch <= AttackEndPitchRotation)
		{
			EndAttack();
		}
	}
	// 아닌 경우 (대기?상태)
	else
	{
		if (bIsReadyToAttack)
		{
			Attack();
		}
		else
		{
			ReadyAttack(DeltaSeconds);
		}
	}
}

void AEnemyBase::Attack()
{
	bIsReadyToAttack = false;
	bIsAttack = true;
	TestWeapon->SetAttackMode(bIsAttack);
}

void AEnemyBase::Defence()
{
	bIsDefence = true;
	TestWeapon->SetDefenceMode(bIsDefence);
	RightHandMesh->SetRelativeLocation(FVector(DefecneDistance, 0, 0));
	PitchRotator.Pitch = 0.0f;
}

void AEnemyBase::Release()
{
	bIsDefence = false;
	TestWeapon->SetDefenceMode(bIsDefence);
	RightHandMesh->SetRelativeLocation(FVector(AttackDistance, 0, 0));
}

void AEnemyBase::EndAttack()
{
	bIsAttack = false;
	TestWeapon->SetAttackMode(bIsAttack);
}

void AEnemyBase::RotateHand()
{
	
}

void AEnemyBase::ReadyAttack(float DeltaSeconds)
{
	PitchRotator.Pitch -= ReadySpeed * DeltaSeconds;

	if (PitchRotator.Pitch >= AttackStartPitchRotation)
	{
		bIsReadyToAttack = true;
	}
}