// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

#include <Kismet/KismetMathLibrary.h>

#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Character/CharacterBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetHiddenInGame(false);
	BoxComponent->SetBoxExtent(FVector(40.f, 2.f, 2.f));
	BoxComponent->SetLineThickness(2.0f);
	SetRootComponent(BoxComponent);	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));


	
	BashEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BashEffect"));
	BashEffect->SetupAttachment(WeaponMesh);

	WeaponEndLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponEndLocation"));
	WeaponEndLocation->SetupAttachment(RootComponent);
	WeaponEndLocation->SetRelativeLocation(FVector(40.f, 0.f, 30.f));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnBoxComponentBeginOverlap);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// OldLocation = CurrentLocation;
	// CurrentLocation = WeaponEndLocation->GetComponentLocation();

	GetWeaponAngleVector();
}

void AWeaponBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Todo : 지금 AEnemyBase로 되어있는데 GetAttackAngle 함수를 CharacterBase에 구현 후 CharacterBase로 Cast하도록 바꿔야함
	
	// UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap"));
	
	if (bIsAttackMode == false) return;
	
	
	// UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap"));
	if (ACharacterBase* Character = Cast<ACharacterBase>(OtherActor))
	{
		if (Character == OwningPlayer) return;

		// 방어든 공격이든 상관없이 검의 충돌 처리를 꺼줌 (언제 켜줄지가 문제)
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
		if (Character->IsDefence())
		{	
			float Value = WeaponAngleVector.GetSafeNormal().Dot(Character->GetWeapon()->GetWeaponAngleVector().GetSafeNormal());
			Value = Value >= 0.0f ? Value : -Value; 
			// UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) Dot Result : %f"), Value);
			if (Value <= DefenceSuccessValue)
			{
				//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 3.0f, 0, 3.0f);
				//DrawDebugLine(GetWorld(), OwningPlayer->GetActorLocation(), OwningPlayer->GetActorLocation() + ForwardVector, FColor::Red , false, 3.0f, 0, 3.0f);
				// Todo : Fail 시 상대방이 따라오는 기능 필요
				OwningPlayer->FailAttack();
				OwningPlayer->StartStun();
				Character->SuccessDefence();
				
				UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) Defence : %f"), Value);
				return;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) Attack : %f"), Value);
			}
		}

		// DrawDebugLine(GetWorld(), WeaponEndLocation->GetComponentLocation(), WeaponEndLocation->GetComponentLocation() + DeltaVector * 100.0f, FColor::Magenta, false, 3.0f, 0, 3.0f);
		// DrawDebugLine(GetWorld(), OwningPlayer->GetActorLocation(), OwningPlayer->GetActorLocation() + ForwardVector, FColor::Red , false, 3.0f, 0, 3.0f);

		// Todo : Move 기능이 약간 이상함
		Character->ReceiveDamage();
		OwningPlayer->SuccessAttack();
	}
}

void AWeaponBase::SetOwningPlayer(ACharacterBase* NewOwningPlayer)
{
	OwningPlayer = NewOwningPlayer;
}

void AWeaponBase::SetAttackMode(bool bIsNewAttackMode)
{
	bIsAttackMode = bIsNewAttackMode;

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWeaponBase::SetDefenceMode(bool bIsNewDefenceMode)
{
	bIsDefenceMode = bIsNewDefenceMode;
}

FVector AWeaponBase::GetWeaponEndLocation() const
{
	return WeaponEndLocation->GetComponentLocation();
}

FVector AWeaponBase::GetWeaponAngleVector()
{
	// Rotation Part
		
	WeaponAngleVector = GetActorLocation() - WeaponEndLocation->GetComponentLocation();
	WeaponAngleVector.Normalize();
	//
	FVector StartLocation = WeaponEndLocation->GetComponentLocation();
	FVector EndLocation = StartLocation + (WeaponAngleVector * 100.0f);

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);

	FRotator TransformedRotation = FTransform(OwningPlayer->GetActorRotation()).InverseTransformRotation(LookAtRotation.Quaternion()).Rotator();

	WeaponAngleVector = FVector(1, 0, 0);
	WeaponAngleVector = TransformedRotation.RotateVector(WeaponAngleVector);
	WeaponAngleVector *= 100.0f;
	WeaponAngleVector.X = 0.0f;

	WeaponAngleVector = FTransform(OwningPlayer->GetActorRotation()).TransformPosition(WeaponAngleVector);

	DrawDebugLine(GetWorld(), StartLocation, StartLocation + WeaponAngleVector * 100.0f, FColor::Blue, false, 0, 0, 3.0f);
	
	//
	// // 시작점에서 끝점을 바라보기 위한 회전값 (월드좌표 기준)
	// 
	//
	// // 월드좌표 기준 회전값을 로컬 좌표로 바꾼다
	// 
	//
	// // 플레이어의 앞방향 벡터 (월드좌표 기준)
	// 
	//
	// // 앞방향 벡터를 로컬좌표 기준 회전값으로 회전시킴 (야직 월드좌표)
	// 
	//
	// // 벡터에 길이를 100으로 늘림
	// 
	//
	// // 벡터의 X값을 0으로 (앞방향 무시, 위와 옆방향만 쓰겠다)
	// 
	//
	// // 해당 해당 벡터를 플레이어의 월드 회전값 기준으로 다시 옮김 (왜지?)
	// 
	//
	// UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) LookAtRotation : %s, TransformedRotation : %s"), *LookAtRotation.ToString(), *TransformedRotation.ToString());
	
	return WeaponAngleVector;
}