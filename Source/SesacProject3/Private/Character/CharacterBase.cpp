// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "MyGameStateBase.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	LeftHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>("LeftHandMesh");
	RightHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>("RightHandMesh");
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetGameState<AMyGameStateBase>()->AddPlayer(this);	
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bMove) // 공격 성공, 방어 성공
	{
		MoveTime += DeltaTime;
		
		FVector NewLocation = FMath::Lerp(GetActorLocation(), Destination, MoveTime);
		SetActorLocation(NewLocation);
		
		if (MoveTime > 1.0f)
		{
			MoveTime = 0.0f;
			bMove = false;
		}
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

// 공격 성공
void ACharacterBase::SuccessAttack()
{
	MoveVertical(MoveDistance);
}

// 방어 성공
void ACharacterBase::SuccessDefence()
{
	MoveVertical(MoveDistance);
}

// 피격
void ACharacterBase::ReceiveDamage()
{
	MoveVertical(MoveDistance * -1);
	
	if (bIsStun)
	{
		StopStun();
	}
}

// 공격 실패
void ACharacterBase::FailAttack()
{
	MoveVertical(MoveDistance * -1);
	
	StartStun();
}

void ACharacterBase::MoveVertical(float Distance)
{
	Destination = GetActorLocation() + GetActorForwardVector() * Distance;
	bMove = true;
	
	UE_LOG(LogTemp, Warning, TEXT("CurrentLocation : %s"), *GetActorLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Destination : %s"), *Destination.ToString());
}

void ACharacterBase::MoveHorizontal()
{
	
	// SetActorLocation(GetActorLocation() + GetActorRightVector() * MoveHorizontalDistance);
}

void ACharacterBase::StartStun()
{
	bIsStun = true;

	// 일정 시간 동안 입력 무시
	// 일정 시간 이후 또는 맞으면 원복
	UE_LOG(LogTemp, Warning, TEXT("Start Stun"));
	
	if (StunTimerHandler.IsValid()) GetWorldTimerManager().ClearTimer(StunTimerHandler);
	GetWorldTimerManager().SetTimer(StunTimerHandler, this, &ACharacterBase::StopStun, StunTime, false, StunTime);
}

void ACharacterBase::StopStun()
{
	bIsStun = false;

	UE_LOG(LogTemp, Warning, TEXT("Stop Stun"));
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
