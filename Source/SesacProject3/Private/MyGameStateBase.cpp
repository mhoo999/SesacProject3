// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

#include "MyGameInstance.h"
#include "MyGameModeBase.h"

#include "Character/CharacterBase.h"

AMyGameStateBase::AMyGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsRoundStarted == false) return;
	
	// CurrentRoundTime -= DeltaSeconds;
	//
	// if (CurrentRoundTime <= 0.0f)
	// {
	// 	// Draw
	// 	SetLoseCharacter(nullptr);
	// }
	// else
	// {
	// 	RoundTimeChanged.ExecuteIfBound(CurrentRoundTime);
	// }

	// UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::Tick) Round : %d, RoundTime : %f"), WinResultArray.Num() + 1, CurrentRoundTime);
}
void AMyGameStateBase::AddPlayer(ACharacterBase* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::AddPlayer) Player : %s, TotalPlayer Num : %d"), *NewPlayer->GetActorNameOrLabel(), PlayerArray.Num());

	if (AMyGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode<AMyGameModeBase>())
	{
		EGameMode GameModeType = GetGameInstance<UMyGameInstance>()->GetGameMode();
		
		if (GameModeType == EGameMode::SINGLE && PlayerArray.Num() == 1)
		{
			GameModeBase->PlaySingle();
		}
		else if (GameModeType == EGameMode::MULTI && PlayerArray.Num() == 2)
		{
			GameModeBase->PlayMulti();
		}
	}
}

void AMyGameStateBase::SetLoseCharacter(ACharacterBase* NewLoseCharacter)
{
	// bIsRoundStarted = false;
	//
	// if (NewLoseCharacter == nullptr)
	// {
	// 	// Draw
	// 	UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) %d Round : Draw"), WinResultArray.Num() + 1);
	// 	WinResultArray.Add(0);
	// 	WinResultAdded.ExecuteIfBound(0);
	// }
	// else if (NewLoseCharacter == Player1)
	// {
	// 	// Player1 Lose
	// 	UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) %d Round : Player2 Win"), WinResultArray.Num() + 1);
	// 	WinResultArray.Add(2);
	// 	WinResultAdded.ExecuteIfBound(2);
	// }
	// else
	// {
	// 	// Player2 Lose
	// 	UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) %d Round : Player1 Win"), WinResultArray.Num() + 1);
	// 	WinResultArray.Add(1);
	// 	WinResultAdded.ExecuteIfBound(1);
	// }
	// MoveToNextRound();
}

void AMyGameStateBase::MoveToNextRound()
{
	// Todo : 나중엔 무승부 체크해서 경기장 축소시키고 4라운드 진행해야함
	if (WinResultArray.Num() >= 3)
	{
		// Check Result
		int32 Player1WinCount = 0;
		int32 Player2WinCount = 0;
		
		for (int32 Iter : WinResultArray)
		{
			if (Iter == 1)
			{
				Player1WinCount++;
			}
			else if (Iter == 2)
			{
				Player2WinCount++;
			}
		}

		if (Player1WinCount > Player2WinCount)
		{
			// Todo : 승리처리
			UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::MoveToNextRound) Player1 Win!!"));
			return;
		}
		else if (Player2WinCount > Player1WinCount)
		{
			// Todo : 승리처리
			UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::MoveToNextRound) Player2 Win!!"));
			return;
		}
		else
		{
			if (WinResultArray.Num() == 3)
			{
				// Todo : 경기장 축소
			}
			else
			{
				// Todo : 무승부 처리
				UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::MoveToNextRound) Draw!!"));
				return;
			}
		}
	}

	// // Todo Something
	//
	// Player1->SetActorLocation(Player1Start->GetActorLocation());
	// Player2->SetActorLocation(Player2Start->GetActorLocation());
	//
	// // Todo : Rotatoin이 적용되지 않음 
	// Player1->SetActorRotation(Player1Start->GetActorRotation());
	// Player2->SetActorRotation(Player2Start->GetActorRotation());
	//
	// bIsRoundStarted = true;
	//
	// CurrentRoundTime = MaxRoundTime;
}

bool AMyGameStateBase::IsRoundStarted() const
{
	return bIsRoundStarted;
}

void AMyGameStateBase::StartRound()
{
	bIsRoundStarted = true;
}