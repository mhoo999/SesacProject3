// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoundWidget.generated.h"

class UHorizontalBox;
class UImage;
UCLASS()
class SESACPROJECT3_API URoundWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void HideCount(float InDeltaTime);
	void HideStart(float InDeltaTime);

	void ShowStartImage();
	void ShowFinishImage();

	float CountOpacity;
	float StartOpacity;
	
	void SetCount(int32 CurrentCount);

	void SetResult(int32 CurrentRound, bool bWin);

	UPROPERTY(Meta= (BindWidget))
	UImage* Img_Count;

	UPROPERTY(Meta= (BindWidget))
	UImage* Img_Start;
	UPROPERTY(Meta= (BindWidget))
	UImage* Img_Finish;

	UPROPERTY(Meta= (BindWidget))
	UHorizontalBox* HB_Result;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> CountTextureArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* WinImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* LoseImage;
};