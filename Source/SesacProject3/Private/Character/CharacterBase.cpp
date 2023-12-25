// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "Components/CapsuleComponent.h"

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
	// AdvanceDistance만큼 Vertical 이동
	MoveVertical(AdvanceDistance);
}

void ACharacterBase::FailAttack()
{
	// AttackFailknockbackDistance만큼 Vertical 이동
	MoveVertical(AttackFailknockbackDistance);

	StartStun();
}

void ACharacterBase::ReceiveDamage()
{
	// ReceiveDamageknockbackDistance만큼 Vertical 이동
	MoveVertical(ReceiveDamageknockbackDistance);
}

void ACharacterBase::MoveVertical(float VerticalDistance)
{
	// 이동하고자 하는 Location
	FVector TargetLocation(VerticalDistance, 0, 0);
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// 현재 위치와 새 위치를 보간하여 새 위치를 계산
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, VerticalInterpSpeed);
	// 계산 된 위치로 이동
	SetActorLocation(NewLocation);
}

void ACharacterBase::MoveHorizontal()
{
	// 이동하고자 하는 Location
	FVector TargetLocation(0, MoveHorizontalDistance, 0);
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	// 현재 위치와 새 위치를 보간하여 새 위치를 계산
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, MoveHorizontalInterpSpeed);
	// 계산 된 위치로 이동
	SetActorLocation(NewLocation);
}

void ACharacterBase::StartStun()
{
	bIsStun = true;

	// 일정 시간 동안 입력 무시
	// 일정 시간 이후 또는 맞으면 원복
}

