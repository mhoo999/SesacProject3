// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "FrameTypes.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>("LeftHandMesh");

	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>("RightHandMesh");
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMove)
	{
		MoveTime += DeltaTime;
	}
	
	if (MoveTime > 1)
	{
		bMove = false;
		MoveTime = 0.0f;
	}
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ACharacterBase::IsDefence()
{
	return true;
}

float ACharacterBase::GetMainHandAngle()
{
	return 0;
}

float ACharacterBase::GetSubHandAngle()
{
	return 0;
}

bool ACharacterBase::IsAttack()
{
	return true;
}

void ACharacterBase::SuccessAttack()
{
	// AttackSuccessDistance만큼 Vertical 전진
	MoveVertical(AttackSuccessDistance);
}

void ACharacterBase::ReceiveDamage()
{
	// AttackSuccessDistance만큼 Vertical 후퇴
	MoveVertical(AttackSuccessDistance * -1);

	if (bIsStun)
	{
		StopStun();
	}
}

void ACharacterBase::SuccessDefence()
{
	// DefenceSuccessDistance만큼 Vertical 전진
	MoveVertical(DefenceSuccessDistance);
}

void ACharacterBase::FailAttack()
{
	// DefenceSuccessDistance만큼 Vertical 후퇴
	MoveVertical(DefenceSuccessDistance * -1);

	StartStun();
}

void ACharacterBase::MoveVertical(float VerticalDistance)
{
	bMove = true;
	// FVector Destination = GetActorLocation() + GetActorForwardVector() * VerticalDistance;
	// FVector NewLocation = FMath::Lerp(GetActorLocation(), Destination, MoveTime);

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * VerticalDistance;
	SetActorLocation(NewLocation);
}

void ACharacterBase::MoveHorizontal()
{
	bMove = true;
	SetActorLocation(GetActorLocation() + GetActorRightVector() * MoveHorizontalDistance);
}

void ACharacterBase::StartStun()
{
	bIsStun = true;

	// 일정 시간 동안 입력 무시
	// 일정 시간 이후 또는 맞으면 원복
	
	if (StunTimerHandler.IsValid()) GetWorldTimerManager().ClearTimer(StunTimerHandler);
	GetWorldTimerManager().SetTimer(StunTimerHandler, this, &ACharacterBase::StopStun, StunTime, false);
}

void ACharacterBase::StopStun()
{
	bIsStun = false;

	// 재동작
}

AWeaponBase* ACharacterBase::GetWeapon()
{
	return Weapon;
}

FVector ACharacterBase::GetAttackAngle()
{
	return FVector();
}
