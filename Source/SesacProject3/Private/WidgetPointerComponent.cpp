// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComponent.h"

// Sets default values for this component's properties
UWidgetPointerComponent::UWidgetPointerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UWidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}