// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/MyPlayerController.h"

#include "MyGameStateBase.h"
#include "Character/CharacterBase.h"

void AMyPlayerController::AddPlayerToGameState_Implementation()
{
 	if (AMyGameStateBase* GameState = GetWorld()->GetGameState<AMyGameStateBase>())
 	{
 		GameState->AddPlayer(Cast<ACharacterBase>(GetCharacter()));
 	}
}
