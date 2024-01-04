// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UButton;
UCLASS()
class SESACPROJECT3_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable)
	void PressSinglePlay();
	UFUNCTION(BlueprintCallable)
	void PressMultiPlay();
	UFUNCTION(BlueprintCallable)
	void PresJoinGame();

	UPROPERTY(EditDefaultsOnly)
	FString TravelURL;
	UPROPERTY(EditDefaultsOnly)
	FString ClientURL;

	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_SinglePlay;
	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_MultiPlay;
	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_JoinGame;
};