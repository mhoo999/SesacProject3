// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyDummy.h"

void AEnemyDummy::AddHandRotaiton()
{
	RollRotator.Roll += 45.0f;
	if (RollRotator.Roll >= 360.0f)
	{
		RollRotator.Roll -= 360.0f;
	}
}