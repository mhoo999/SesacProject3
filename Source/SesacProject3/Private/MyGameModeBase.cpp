// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include <Character/EnemyAI.h>
#include <EngineUtils.h>
#include <GameFramework/PlayerStart.h>

#include "MyGameStateBase.h"
#include "Character/PlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/InGame/RoundWidget.h"

AMyGameModeBase::AMyGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	BGMAudioComponent = UGameplayStatics::SpawnSound2D(this, BGMSound);
}

void AMyGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCountDown)
	{
		CurrentCountTime -= DeltaSeconds;

		if (CurrentCountTime <= 0.0f)
		{
			CurrentCountTime = 1.0f;
			UE_LOG(LogTemp, Warning, TEXT("AMyGameModeBase::Tick) CurrentCount : %d"), CurrentCount);
			if (CurrentCount == 0)
			{
				if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player1))
				{
					PlayerCharacter->GetRoundWidget()->ShowStartImage();
				}
				if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player2))
				{
					PlayerCharacter->GetRoundWidget()->ShowStartImage();
				}
				
				bCountDown = false;
				bIsRoundStarted = true;
			}
			else
			{
				if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player1))
				{
					PlayerCharacter->GetRoundWidget()->SetCount(CurrentCount);
				}
				if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player2))
				{
					PlayerCharacter->GetRoundWidget()->SetCount(CurrentCount);
				}
				CurrentCount--;
			}
		}
	}
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
	CurrentCount = 3;
	bCountDown = true;
	CurrentCountTime = 1.0f;
	
	Player1->SetActorLocation(Player1Start->GetActorLocation());
	Player1->SetActorRotation(Player1Start->GetActorRotation());

	Player1->StopStun();

	Player2->SetActorLocation(Player2Start->GetActorLocation());
	Player2->SetActorRotation(Player2Start->GetActorRotation());

	Player2->StopStun();
}

void AMyGameModeBase::SetLoseCharacter(ACharacterBase* LoseCharacter)
{
	bIsRoundStarted = false;

	ResultArray.Add(LoseCharacter == Player2);
	

	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player1))
	{
		PlayerCharacter->GetRoundWidget()->SetResult(ResultArray.Num(), ResultArray.Top());
	}
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player2))
	{
		PlayerCharacter->GetRoundWidget()->SetResult(ResultArray.Num(), ResultArray.Top());
	}

	if (ResultArray.Num() >= 2)
	{
		int32 Player1WinCount = 0;
		int32 Player2WinCount = 0;

		for (int i = 0; i < ResultArray.Num(); ++i)
		{
			if (ResultArray[i]) Player1WinCount++;
			else Player2WinCount++;
		}

		if (Player1WinCount > Player2WinCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("AMyGameModeBase::SetLoseCharacter) Player1 Final Win"));

			Finish();
		}
		else if (Player1WinCount < Player2WinCount)
		{
			UE_LOG(LogTemp, Warning, TEXT("AMyGameModeBase::SetLoseCharacter) Player2 Final Win"));

			Finish();
		}
		else
		{
			if (ResultArray.Num() == 2)
			{
				StartRound();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AMyGameModeBase::SetLoseCharacter) Final Draw"));

				Finish();
			}
		}
	}
	else
	{
		StartRound();
	}
}

void AMyGameModeBase::Finish()
{
	BGMAudioComponent->Stop();
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player1))
	{
		PlayerCharacter->GetRoundWidget()->ShowFinishImage();
	}
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Player2))
	{
		PlayerCharacter->GetRoundWidget()->ShowFinishImage();
	}
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