// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Main/MainMenuWidget.h"

void UMainMenuWidget::PressSinglePlay()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::PressSinglePlay) "));

	GetWorld()->ServerTravel(TravelURL);
}

void UMainMenuWidget::PressMultiPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::PressMultiPlay) "));

	FString ServerURL = TravelURL + FString(TEXT("?listen"));
	GetWorld()->ServerTravel(ServerURL, true);
}

void UMainMenuWidget::PresJoinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::PresJoinGame) "));

	GetWorld()->GetFirstPlayerController()->ClientTravel(ClientURL, TRAVEL_Absolute);
}