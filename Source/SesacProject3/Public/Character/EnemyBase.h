// OSH

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "EnemyBase.generated.h"

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
private:
	
	void EndAttack();

	void RotateHand();

private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float AttackDistance;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	float AttackSpeed;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	bool bIsAttack;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	FVector AttackDirection;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess, MakeEditWidget))
	FVector HandZeroLocation;
};