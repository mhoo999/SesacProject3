// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class UParticleSystemComponent;
class ACharacterBase;
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

	void SetOwningPlayer(ACharacterBase* NewOwningPlayer);
	void SetAttackMode(bool bIsNewAttackMode);
	void SetDefenceMode(bool bIsNewDefenceMode);

	// Todo FailAttack 을 오버라이딩해서 Enemy에 맞게 변형 필요
	// virtual void FailAttack() override;

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
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	ACharacterBase* OwningPlayer;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	bool bIsAttackMode;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	bool bIsDefenceMode;

	// 두 Vector 를 Dot 했을 때 이 값보다 작으면 방어 성공
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float DefenceSuccessValue = 0.5f;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	USceneComponent* WeaponEndLocation;
};
