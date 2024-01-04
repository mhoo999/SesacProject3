// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::SetGameMode(EGameMode NewGameMode)
{
	GameMode = NewGameMode;
}

EGameMode UMyGameInstance::GetGameMode() const
{
	return GameMode;
}