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

void ACharacterBase::FailAttack()
{
}

void ACharacterBase::SuccessAttack()
{
}

void ACharacterBase::ReceiveDamage()
{
}

void ACharacterBase::MoveHorizontal()
{
}

