// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

#include "InterchangeResult.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Character/CharacterBase.h"
#include "Character/EnemyBase.h"

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
	BashEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BashEffect"));
	BashEffect->SetupAttachment(WeaponMesh);

	WeaponEndLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponEndLocation"));
	WeaponEndLocation->SetupAttachment(RootComponent);
	WeaponEndLocation->SetRelativeLocation(FVector(40.f, 0.f, 0.f));
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


	if (bIsDefenceMode)
	{
		DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (Cast<AEnemyBase>(OwningPlayer)->GetAttackAngle() * 300.0f), FColor::Purple);
	}
}

void AWeaponBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Todo : 지금 AEnemyBase로 되어있는데 GetAttackAngle 함수를 CharacterBase에 구현 후 CharacterBase로 Cast하도록 바꿔야함 
	if (bIsAttackMode == false) return;
	if (AEnemyBase* Character = Cast<AEnemyBase>(OtherActor))
	{
		if (Character == OwningPlayer) return;
			
		if (Character->IsDefence())
		{	
			float Value = Cast<AEnemyBase>(OwningPlayer)->GetAttackAngle().Dot(Character->GetAttackAngle());
			Value = Value >= 0.0f ? Value : -Value; 
			// UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) Dot Result : %f"), Value);
			if (Value <= DefenceSuccessValue)
			{
				// Todo : Fail 시 상대방이 따라오는 기능 필요
				//OwningPlayer->FailAttack();
				UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) Defence : %f"), Value);
				return;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) Attack : %f"), Value);
			}
		}

		// Todo : Move 기능이 약간 이상함
		//Character->ReceiveDamage();
		//OwningPlayer->SuccessAttack();
	}
}

void AWeaponBase::SetOwningPlayer(ACharacterBase* NewOwningPlayer)
{
	OwningPlayer = NewOwningPlayer;
}

void AWeaponBase::SetAttackMode(bool bIsNewAttackMode)
{
	bIsAttackMode = bIsNewAttackMode;
}

void AWeaponBase::SetDefenceMode(bool bIsNewDefenceMode)
{
	bIsDefenceMode = bIsNewDefenceMode;
}