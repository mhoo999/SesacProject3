// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ChargeSword.h"

void AChargeSword::SuccessDefence()
{
	CurrentChargeValue = FMath::Min(CurrentChargeValue + IncreaseChargeValue, MaxChargeValue);
}

float AChargeSword::GetKnockbackDistance()
{
	float ReturnValue = KnockbackDistance * (CurrentChargeValue / MaxChargeValue);

	CurrentChargeValue = 0.0f;
	
	return ReturnValue;
}