// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AEnemyAI;
class ACharacterBase;
class APlayerStart;
UCLASS()
class SESACPROJECT3_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void SetPlayerStart();

	void StartRound();

	void SetLoseCharacter(ACharacterBase* LoseCharacter);
	
	void PlaySingle();
	void PlayMulti();

	bool IsRoundStarted() const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyAI> EnemyAIClass;
	
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	APlayerStart* Player1Start;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	APlayerStart* Player2Start;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	ACharacterBase* Player1;
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess))
	ACharacterBase* Player2;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess))
	bool bIsRoundStarted;
};