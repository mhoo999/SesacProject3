// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include <Character/EnemyAI.h>
#include <EngineUtils.h>
#include <GameFramework/PlayerStart.h>

#include "MyGameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "PlayerController/MyPlayerController.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyGameModeBase::SetPlayerStart()
{
	for (TActorIterator<AActor> It(GetWorld(), APlayerStart::StaticClass()); It; ++It)
	{
		if (It-> GetActorLabel().Compare(TEXT("Player1Start")) == 0)
		{
			Player1Start = Cast<APlayerStart>(*It);
		}
		else
		{
			Player2Start = Cast<APlayerStart>(*It);
		}
	}
}

void AMyGameModeBase::StartRound()
{
	Player1->SetActorLocation(Player1Start->GetActorLocation());
	Player1->SetActorRotation(Player1Start->GetActorRotation());

	Player1->StopStun();

	Player2->SetActorLocation(Player2Start->GetActorLocation());
	Player2->SetActorRotation(Player2Start->GetActorRotation());

	Player1->StopStun();

	bIsRoundStarted = true;
}

void AMyGameModeBase::SetLoseCharacter(ACharacterBase* LoseCharacter)
{
	bIsRoundStarted = false;
}

void AMyGameModeBase::PlaySingle()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::PlaySingle"));

	SetPlayerStart();
	
	Player1 = GameState->PlayerArray[0]->GetPawn<ACharacterBase>();

	Player1->SetActorLocation(Player1Start->GetActorLocation());
	Player1->SetActorRotation(Player1Start->GetActorRotation());

	// Spawn Enemy
	Player2 = Cast<AEnemyBase>(GetWorld()->SpawnActor(EnemyAIClass));

	Player2->SetActorLocation(Player2Start->GetActorLocation());
	Player2->SetActorRotation(Player2Start->GetActorRotation());
	

	Player1->SetTarget(Player2);
	Player2->SetTarget(Player1);

	StartRound();
}

void AMyGameModeBase::PlayMulti()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::PlayMulti"));

	SetPlayerStart();

	auto PlayerArray = GetGameState<AMyGameStateBase>()->PlayerArray;

	for (auto Iter : PlayerArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::PlaySingle) Actor Name : %s"), *Iter->Owner->GetActorNameOrLabel());
	}
}

bool AMyGameModeBase::IsRoundStarted() const
{
	return bIsRoundStarted;
}