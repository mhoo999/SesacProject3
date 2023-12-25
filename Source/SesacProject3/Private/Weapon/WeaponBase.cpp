// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

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
	BashEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BashEffect"));
	BashEffect->SetupAttachment(WeaponMesh);
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

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 300.0f), FColor::Red);
}

void AWeaponBase::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsAttackMode == false) return;
	if (ACharacterBase* Character = Cast<ACharacterBase>(OtherActor))
	{
		if (Character == OwningPlayer) return;

		if (Character->IsDefence())
		{
			Character->GetWeapon();
		}

		Character->ReceiveDamage();
		
		// UE_LOG(LogTemp, Warning, TEXT("AWeaponBase::OnBoxComponentBeginOverlap) Overlapped Actor Label : %s"), *OtherActor->GetActorLabel());
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