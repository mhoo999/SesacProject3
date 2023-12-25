// OSH

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EnemyBase.generated.h"

class AWeaponBase;
/**
 * 
 */
UCLASS()
class SESACPROJECT3_API AEnemyBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AEnemyBase();
	
	virtual void BeginPlay() override;
	virtual bool IsAttack() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(CallInEditor)
	void Attack();
	UFUNCTION(CallInEditor)
	void Defence();
	UFUNCTION(CallInEditor)
	void Release();

	virtual bool IsDefence() override;

	FVector GetAttackAngle();
	
private:
	void EndAttack();

	void RotateHand();

	void ReadyAttack(float DeltaSeconds);

private:
	// Attack
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float AttackDistance;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float AttackSpeed;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	bool bIsAttack;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	FVector AttackDirection;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float AttackStartPitchRotation;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float AttackEndPitchRotation;
	
	// Ready
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float ReadySpeed;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	bool bIsReadyToAttack;

	// Defence
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float DefecneDistance;
	
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess, MakeEditWidget))
	USceneComponent* HandZeroPoint;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	FRotator RollRotator;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	FRotator PitchRotator;
};