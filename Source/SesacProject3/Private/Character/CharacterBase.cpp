// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "MyGameStateBase.h"
#include "Weapon/WeaponBase.h"

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

	// 타겟 설정(내가 아닌 world 내 Character)
	// Target = 
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 타겟을 응시하는 함수
	// GazeAtTarget();
	
	// 공격 성공, 방어 성공, 피격, 공격 실패일 경우 앞뒤로, 방어 상태일 경우 좌우로 이동
	if (bMove)
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
	// 앞으로 MoveDistance 만큼 이동
	MoveVertical(MoveDistance);
}

// 방어 성공
void ACharacterBase::SuccessDefence()
{
	// 앞으로 MoveDistance 만큼 이동
	MoveVertical(MoveDistance);
}

// 피격
void ACharacterBase::ReceiveDamage()
{
	// 못 막았을 때, 방어 상태가 풀리도록
	bIsDefence = false;
	Weapon->SetDefenceMode(false);

	// 뒤로 -MoveDistance 만큼 이동
	MoveVertical(MoveDistance * -1);
	
	if (bIsStun)
	{
		StopStun();
	}
}

// 공격 실패
void ACharacterBase::FailAttack()
{
	// 뒤로 -MoveDistance 만큼 이동
	MoveVertical(MoveDistance * -1);
	
	StartStun();
}

void ACharacterBase::MoveVertical(float Distance)
{
	Destination = GetActorLocation() + GetActorForwardVector() * Distance;
	bMove = true;
}

void ACharacterBase::MoveHorizontal(float SwordAngle)
{
	float MaxValue = 180.0f;
	float MinValue = 0.0f;
	
	// 검의 벡터 값을 받아서 0-1값으로 정규화
	float NewAngle = (SwordAngle - MinValue) / (MaxValue - MinValue);

	// 정규화된 값을 이용해서 새로운 Distance 도출
	float NewDistance = MoveHorizontalDistance * NewAngle;
	
	Destination = GetActorLocation() + GetActorRightVector() * NewDistance;
	bMove = true;
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

void ACharacterBase::GazeAtTarget()
{
	// 목표 지점에서 현재 위치로 향하는 벡터를 계산
	FVector Direction = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	// 계산된 방향 벡터를 Rotator로 변환
	FRotator TargetRotator = Direction.Rotation();
	
	SetActorRotation(TargetRotator);
}
