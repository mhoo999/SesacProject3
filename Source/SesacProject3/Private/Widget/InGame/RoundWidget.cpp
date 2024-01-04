// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InGame/RoundWidget.h"
#include <Components/Image.h>

void URoundWidget::HideCount()
{
	CountOpacity -= GetWorld()->GetDeltaSeconds();

	if (CountOpacity <= 0.0f)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(CountHideTimer);
		Img_Count->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Img_Count->SetOpacity(CountOpacity);
	}
}

void URoundWidget::SetCount(int32 CurrentCount)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (CountHideTimer.IsValid())
	{
		TimerManager.ClearTimer(CountHideTimer);
	}
	Img_Count->SetVisibility(ESlateVisibility::HitTestInvisible);
	Img_Count->SetBrushFromTexture(CountTextureArray[CurrentCount - 1]);

	TimerManager.SetTimer(CountHideTimer, this, &URoundWidget::HideCount, 0.1f, true);
}