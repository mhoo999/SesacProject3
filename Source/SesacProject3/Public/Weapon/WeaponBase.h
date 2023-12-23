// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class UParticleSystemComponent;
UCLASS()
class SESACPROJECT3_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	

protected:
	UPROPERTY(EditDefaultsOnly)
	float KnockbackDistance;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* WeaponMesh;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* BashEffect;

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	bool bIsAttackMode;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	bool bIsDefenceMode;
};
