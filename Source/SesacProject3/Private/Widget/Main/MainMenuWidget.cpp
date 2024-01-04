// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Main/MainMenuWidget.h"

#include "MyGameInstance.h"
#include "Components/Button.h"

bool UMainMenuWidget::Initialize()
{
	if (Super::Initialize() == false) return false;

	Btn_SinglePlay->OnClicked.AddDynamic(this, &UMainMenuWidget::PressSinglePlay);
	Btn_MultiPlay->OnClicked.AddDynamic(this, &UMainMenuWidget::PressMultiPlay);
	Btn_JoinGame->OnClicked.AddDynamic(this, &UMainMenuWidget::UMainMenuWidget::PresJoinGame);
	
	return true;
}

void UMainMenuWidget::PressSinglePlay()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::PressSinglePlay) "));

	GetGameInstance<UMyGameInstance>()->SetGameMode(EGameMode::SINGLE);

	GetWorld()->ServerTravel(TravelURL);
}

void UMainMenuWidget::PressMultiPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::PressMultiPlay) "));

	GetGameInstance<UMyGameInstance>()->SetGameMode(EGameMode::MULTI);
	
	FString ServerURL = TravelURL + FString(TEXT("?listen"));
	GetWorld()->ServerTravel(ServerURL, true);
}

void UMainMenuWidget::PresJoinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("UMainMenuWidget::PresJoinGame) "));

	GetWorld()->GetFirstPlayerController()->ClientTravel(ClientURL, TRAVEL_Absolute);
}