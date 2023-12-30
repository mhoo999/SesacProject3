// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

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
	if (NewLoseCharacter == Player1)
	{
		// Player1 Lose
		UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) Player1 Lose"));
	}
	else
	{
		// Player2 Lose
		UE_LOG(LogTemp, Warning, TEXT("AMyGameStateBase::SetLoseCharacter) Player2 Lose"));
	}
}