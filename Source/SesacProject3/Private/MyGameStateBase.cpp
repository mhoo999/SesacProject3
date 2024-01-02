// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

#include "Character/CharacterBase.h"

#include <EngineUtils.h>
#include <GameFramework/PlayerStart.h>

AMyGameStateBase::AMyGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyGameStateBase::BeginPlay()
{
	Super::BeginPlay();

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

	GetWorld()->GetTimerManager().SetTimer(WaitForPlayerReadyTimer, this, &AMyGameStateBase::WaitForPlayerReady, 1.0f, true);
}

void AMyGameStateBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsRoundStarted == false) return;
	
	CurrentRoundTime -= DeltaSeconds;

	if (CurrentRoundTime <= 0.0f)
	{
		// Draw
		SetLoseCharacter(nullptr);
	}
	else
	{
		RoundTimeChanged.ExecuteIfBound(CurrentRoundTime);
	}

	// UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::Tick) Round : %d, RoundTime : %f"), WinResultArray.Num() + 1, CurrentRoundTime);
}

void AMyGameStateBase::AddPlayer(ACharacterBase* NewPlayer)
{
	if (HasAuthority() == false) return;

	if (Player1 == nullptr)
	{
		Player1 = NewPlayer;
	}
	else if (Player2 == nullptr)
	{
		Player2 = NewPlayer;
	}
}

void AMyGameStateBase::SetLoseCharacter(ACharacterBase* NewLoseCharacter)
{
	if (NewLoseCharacter == nullptr)
	{
		// Draw
		UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) %d Round : Draw"), WinResultArray.Num() + 1);
		WinResultArray.Add(0);
		WinResultAdded.ExecuteIfBound(0);
	}
	else if (NewLoseCharacter == Player1)
	{
		// Player1 Lose
		UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) %d Round : Player2 Win"), WinResultArray.Num() + 1);
		WinResultArray.Add(2);
		WinResultAdded.ExecuteIfBound(2);
	}
	else
	{
		// Player2 Lose
		UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) %d Round : Player1 Win"), WinResultArray.Num() + 1);
		WinResultArray.Add(1);
		WinResultAdded.ExecuteIfBound(1);
	}
	MoveToNextRound();
}

ACharacterBase* AMyGameStateBase::GetOtherCharacter(ACharacterBase* CurrentCharacter)
{
	if (CurrentCharacter == Player1) return Player2;
	
	return Player1;
}

void AMyGameStateBase::MoveToNextRound()
{
	bIsRoundStarted = false;
	// Round 수

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

	// Todo Something
	
	Player1->SetActorLocation(Player1Start->GetActorLocation());
	Player2->SetActorLocation(Player2Start->GetActorLocation());

	Player1->SetActorRotation(Player1Start->GetActorRotation());

	// Todo : Rotatoin이 적용되지 않음 
	Player2->SetActorRotation(Player2Start->GetActorRotation());

	bIsRoundStarted = true;

	CurrentRoundTime = MaxRoundTime;
}

bool AMyGameStateBase::IsRoundStarted() const
{
	return bIsRoundStarted;
}

void AMyGameStateBase::StartRound()
{
	bIsRoundStarted = true;
}

void AMyGameStateBase::WaitForPlayerReady()
{
	if (Player1 != nullptr && Player2 != nullptr)
	{
		GetWorld()->GetTimerManager().ClearTimer(WaitForPlayerReadyTimer);
		MoveToNextRound();
	}
}