// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

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
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * VerticalDistance);
}

void ACharacterBase::MoveHorizontal()
{
	SetActorLocation(GetActorLocation() + GetActorRightVector() * MoveHorizontalDistance);
}

void ACharacterBase::StartStun()
{
	bIsStun = true;

	// 일정 시간 동안 입력 무시
	// 일정 시간 이후 또는 맞으면 원복
}

AWeaponBase* ACharacterBase::GetWeapon()
{
	return Weapon;
}

FVector ACharacterBase::GetAttackAngle()
{
	return FVector();
}
