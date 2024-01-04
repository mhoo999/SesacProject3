// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundWidget.generated.h"

class UImage;
UCLASS()
class SESACPROJECT3_API URoundWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void HideCount();

	float CountOpacity;
	
	void SetCount(int32 CurrentCount);

	UPROPERTY(Meta= (BindWidget))
	UImage* Img_Count;

	UPROPERTY(Meta= (BindWidget))
	UImage* Img_Start;
	UPROPERTY(Meta= (BindWidget))
	UImage* Img_Finish;

	FTimerHandle CountHideTimer; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> CountTextureArray;
};