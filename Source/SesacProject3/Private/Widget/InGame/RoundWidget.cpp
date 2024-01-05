// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InGame/RoundWidget.h"
#include <Components/Image.h>

#include "Components/HorizontalBox.h"

void URoundWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Img_Count->GetVisibility() == ESlateVisibility::Visible)
	{
		HideCount(InDeltaTime);
	}

	if (Img_Start->GetVisibility() == ESlateVisibility::Visible)
	{
		HideStart(InDeltaTime);
	}
}

void URoundWidget::HideCount(float InDeltaTime)
{
	CountOpacity -= InDeltaTime;

	if (CountOpacity <= 0.0f)
	{
		Img_Count->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Img_Count->SetOpacity(CountOpacity);
	}
}

void URoundWidget::HideStart(float InDeltaTime)
{
	StartOpacity -= InDeltaTime;

	if (StartOpacity <= 0.0f)
	{
		Img_Start->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Img_Start->SetOpacity(StartOpacity);
	}
}

void URoundWidget::ShowStartImage()
{
	StartOpacity = 1.f;
	Img_Start->SetOpacity(StartOpacity);
	Img_Start->SetVisibility(ESlateVisibility::Visible);
}

void URoundWidget::ShowFinishImage()
{
	Img_Finish->SetVisibility(ESlateVisibility::Visible);
}

void URoundWidget::SetCount(int32 CurrentCount)
{
	CountOpacity = 1.f;
	Img_Count->SetOpacity(CountOpacity);
	Img_Count->SetVisibility(ESlateVisibility::Visible);
	Img_Count->SetBrushFromTexture(CountTextureArray[CurrentCount - 1]);
}

void URoundWidget::SetResult(int32 CurrentRound, bool bWin)
{
	Cast<UImage>(HB_Result->GetChildAt((CurrentRound - 1) * 2))->SetBrushFromTexture(bWin ? WinImage : LoseImage);
}