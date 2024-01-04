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
	// Stun
	virtual void StartStun() override;
	virtual void StopStun() override;
	// Getter
	virtual bool IsAttack() override;
	virtual bool IsDefence() override;
	// Action
	UFUNCTION(CallInEditor, BlueprintCallable)
	virtual void Attack();
	UFUNCTION(CallInEditor, BlueprintCallable)
	virtual void Defence();
	UFUNCTION(CallInEditor, BlueprintCallable)
	void Release();

	virtual void Tick(float DeltaSeconds) override;	

	virtual FVector GetAttackAngle() override;

protected:
	virtual void GazeAtTarget() override;
	
	virtual void EndAttack();

	bool RotateHand(float DeltaSeconds);
	
	// Player
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	ACharacterBase* EnemyPlayer;

	// Weapon
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeaponBase> WeaponClass;
	
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
	
	// Defence
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float DefecneDistance;
	
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess, MakeEditWidget))
	USceneComponent* HandZeroPoint;

	// Rotation
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float RotationTolerance;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float HandRotateSpeed;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	float TargetRollRotation;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	FRotator RollRotator;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	FRotator PitchRotator;
	
	UPROPERTY(VisibleInstanceOnly)
	bool bIsTargetPlayer;
};