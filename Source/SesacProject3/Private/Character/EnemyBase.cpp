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
}

bool AEnemyBase::IsAttack()
{
	return bIsAttack;
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
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
	// 방어 중인 경우 (방어를 몇초 하다가 공격으로 전환할 것인지 체크)
	else if (bIsDefence)
	{
		// 플레이어의 각도를 따라갈 것인지?
		// 일정 각도로 돌아갈 것인지?

		if (RotateHand(DeltaSeconds))
		{
			Attack();
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

	TargetRollRotation = FMath::RandRange(0.0f, 359.0f);
	
	Defence();
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