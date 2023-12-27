// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

#include "Weapon/WeaponBase.h"

AEnemyBase::AEnemyBase()
{
	HandZeroPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HandZeroPoint"));
	HandZeroPoint->SetupAttachment(RootComponent);
	RightHandMesh->SetupAttachment(HandZeroPoint);
	LeftHandMesh->SetupAttachment(HandZeroPoint);
}

void AEnemyBase::StartStun()
{
	Super::StartStun();
	EndAttack();
	Release();
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	//RightHandMesh->SetRelativeLocation(HandZeroLocation + FVector(0, 0, AttackDistance));

	// Spawn Sword
	Weapon = GetWorld()->SpawnActor<AWeaponBase>();

	Weapon->AttachToComponent(RightHandMesh, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Weapon->SetActorRelativeLocation(FVector(33, 21, -3));
	Weapon->SetActorRelativeRotation(FRotator(0, 20, 0));
	Weapon->SetOwningPlayer(this);

	EnemyPlayer = Cast<ACharacterBase>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	// UE_LOG(LogTemp, Warning, TEXT("AEnemyBase::BeginPlay) EnemyPlayer Name : %s"), *EnemyPlayer->GetActorNameOrLabel());

	LeftHandMesh->AttachToComponent(RightHandMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

bool AEnemyBase::IsAttack()
{
	return bIsAttack;
}

void AEnemyBase::Attack()
{
	Release();
	bIsReadyToAttack = false;
	bIsAttack = true;
	Weapon->SetAttackMode(bIsAttack);
}

void AEnemyBase::Defence()
{
	bIsAttack = false;
	bIsDefence = true;
	Weapon->SetDefenceMode(bIsDefence);
	RightHandMesh->SetRelativeLocation(FVector(DefecneDistance, 0, 0));
	// PitchRotator.Pitch = 0.0f;
}

void AEnemyBase::Release()
{
	bIsDefence = false;
	Weapon->SetDefenceMode(bIsDefence);
	RightHandMesh->SetRelativeLocation(FVector(AttackDistance, 0, 0));
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsStun) return;

	HandZeroPoint->SetRelativeRotation(FTransform(RollRotator).TransformRotation(bIsDefence ? FQuat::Identity : PitchRotator.Quaternion()));
	
	// 공격 중인 경우
	if (bIsAttack)
	{
		//HandZeroPoint->AddLocalRotation(FRotator(AttackSpeed * DeltaSeconds,0,0));

		PitchRotator.Pitch += DeltaSeconds * AttackSpeed;

		if (PitchRotator.Pitch <= AttackEndPitchRotation)
		{
			EndAttack();
		}
	}
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

void AEnemyBase::EndAttack()
{
	bIsAttack = false;
	Weapon->SetAttackMode(bIsAttack);

	RollRotator.Roll += 180.f;
	PitchRotator.Pitch = AttackStartPitchRotation;

	if (RollRotator.Roll >= 360.f) RollRotator.Roll -= 360.f;
}

bool AEnemyBase::RotateHand(float DeltaSeconds)
{
	if (RollRotator.Roll > TargetRollRotation) RollRotator.Roll -= DeltaSeconds * HandRotateSpeed;
	else if (RollRotator.Roll < TargetRollRotation) RollRotator.Roll += DeltaSeconds * HandRotateSpeed;

	if (FMath::RandRange(0.0f, 100.0f) <= 5.0f)
	{
		TargetRollRotation *= -1;
	}

	if (FMath::Abs(RollRotator.Roll - TargetRollRotation) <= RotationTolerance)
	{
		return true;
	}
	
	return false;
}

void AEnemyBase::ReadyAttack(float DeltaSeconds)
{
	PitchRotator.Pitch -= ReadySpeed * DeltaSeconds;

	if (PitchRotator.Pitch >= AttackStartPitchRotation)
	{
		bIsReadyToAttack = true;
	}
}