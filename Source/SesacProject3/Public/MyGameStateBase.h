// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

class ACharacterBase;
/**
 * 
 */
UCLASS()
class SESACPROJECT3_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	void AddPlayer(ACharacterBase* NewPlayer);
	void SetLoseCharacter(ACharacterBase* NewLoseCharacter);
private:
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	ACharacterBase* Player1;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	ACharacterBase* Player2; 
};