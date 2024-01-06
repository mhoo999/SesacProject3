// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AEnemyAI;
class ACharacterBase;
class APlayerStart;
class USoundBase;
class UAudioComponent;
UCLASS()
class SESACPROJECT3_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void SetPlayerStart();

	void StartRound();

	void SetLoseCharacter(ACharacterBase* LoseCharacter);

	void Finish();
	
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

	bool bCountDown;
	int32 CurrentCount;
	float CurrentCountTime = 1.0f;

	TArray<bool> ResultArray;

	// Sound
	UPROPERTY(EditDefaultsOnly)
	USoundBase* BGMSound;
	UPROPERTY(EditDefaultsOnly)
	USoundBase* FinishSound;
	UAudioComponent* BGMAudioComponent;
};