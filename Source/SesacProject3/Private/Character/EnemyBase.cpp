// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

#include <Components/ArrowComponent.h>

#include "Weapon/WeaponBase.h"
#include "MyGameStateBase.h"
#include "Character/PlayerCharacter.h"

AEnemyBase::AEnemyBase()
{
	HandZeroPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HandZeroPoint"));
	HandZeroPoint->SetupAttachment(RootComponent);
	RightHandMesh->SetupAttachment(HandZeroPoint);
	LeftHandMesh->SetupAttachment(HandZeroPoint);

	// GetArrowComponent()->SetHiddenInGame(false);
}

void AEnemyBase::StartStun()
{
	Super::StartStun();

	bIsAttack = false;
	bIsDefence = false;
}

void AEnemyBase::StopStun()
{
	Super::StopStun();

	EndAttack();
	Defence();
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	// Spawn Sword
	if (WeaponClass)
	{
		Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
        Weapon->AttachToComponent(RightHandMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
        Weapon->SetActorRelativeLocation(FVector(30, 20, -3));
        Weapon->SetActorRelativeRotation(FRotator(0, 20, 0));
        Weapon->SetOwningPlayer(this);
	}

	EnemyPlayer = Cast<ACharacterBase>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	// UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::BeginPlay) EnemyPlayer Name : %s"), *EnemyPlayer->GetActorNameOrLabel());

	LeftHandMesh->AttachToComponent(RightHandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	if (Cast<APlayerCharacter>(Target))
	{
		bIsTargetPlayer = true;
	}
}

bool AEnemyBase::IsAttack()
{
	return bIsAttack;
}

void AEnemyBase::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::Attack) %s's Attack"), *GetActorNameOrLabel());
	Release();
	bIsAttack = true;
	Weapon->SetAttackMode(bIsAttack);
}

void AEnemyBase::Defence()
{
	bIsDefence = true;
	Weapon->SetDefenceMode(bIsDefence);
	RightHandMesh->SetRelativeLocation(FVector(DefecneDistance, 0, 0));
}

void AEnemyBase::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::Release) %s's Release"), *GetActorNameOrLabel());
	bIsDefence = false;
	Weapon->SetDefenceMode(bIsDefence);
	RightHandMesh->SetRelativeLocation(FVector(AttackDistance, 0, 0));
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GazeAtTarget();
	
	if (bIsStun) return;

	HandZeroPoint->SetRelativeRotation(FTransform(RollRotator).TransformRotation(bIsDefence ? FQuat::Identity : PitchRotator.Quaternion()));
}

bool AEnemyBase::IsDefence()
{
	return bIsDefence;
}

FVector AEnemyBase::GetAttackAngle()
{
	FVector AttackAngle = FTransform(GetActorRotation()).TransformRotation(RollRotator.Quaternion()).RotateVector(GetActorUpVector());
	return AttackAngle;
}

void AEnemyBase::GazeAtTarget()
{
	Super::GazeAtTarget();

	if (Target)
	{
		FVector Direction = Target->GetActorLocation() - GetActorLocation();
        Direction.Z = 0.0f;
        SetActorRotation(FRotationMatrix::MakeFromX(Direction).Rotator());
	}
}

void AEnemyBase::EndAttack()
{
	bIsAttack = false;
	Weapon->SetAttackMode(bIsAttack);

	RollRotator.Roll += 180.f;
	PitchRotator.Pitch = AttackStartPitchRotation;

	if (RollRotator.Roll >= 360.f) RollRotator.Roll -= 360.f;
	if (RollRotator.Roll >= 180.f) RollRotator.Roll -= 360.f;
}

bool AEnemyBase::RotateHand(float DeltaSeconds)
{
	if (bIsTargetPlayer)
	{
		// TargetRollRotation = Target->GetRollRotation();

		// Todo : 난이도 -> TargetRollRotation 에 얼마나 큰 오차를 줄 것인가?
		/*
		 * Arange = FMath::RandRange(-10, 10) + FMath::RandRange(-10, 10);
		 * Arange += Arange > 0 ?
		 */
	}

	if (RollRotator.Roll > TargetRollRotation) RollRotator.Roll -= DeltaSeconds * HandRotateSpeed;
	else if (RollRotator.Roll < TargetRollRotation) RollRotator.Roll += DeltaSeconds * HandRotateSpeed;

	if (FMath::Abs(RollRotator.Roll - TargetRollRotation) <= RotationTolerance)
	{
		return true;
	}
	
	return false;
}