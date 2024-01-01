// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WeaponBase.h"
#include "ChargeSword.generated.h"

/**
 * 
 */
UCLASS()
class SESACPROJECT3_API AChargeSword : public AWeaponBase
{
	GENERATED_BODY()

public:
	virtual void SuccessDefence() override;

	virtual float GetKnockbackDistance() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	float MaxChargeValue;
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess))
	float IncreaseChargeValue;
	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess))
	float CurrentChargeValue;
};