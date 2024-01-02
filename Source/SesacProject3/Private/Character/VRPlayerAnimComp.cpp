// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VRPlayerAnimComp.h"
#include "Character/VRPlayerAnimInst.h"
#include "Character/PlayerCharacter.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UVRPlayerAnimComp::UVRPlayerAnimComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVRPlayerAnimComp::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Player = GetOwner<APlayerCharacter>();
	bodyAnim = Cast<UVRPlayerAnimInst>(Player->GetMesh()->GetAnimInstance());

}


// Called every frame
void UVRPlayerAnimComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	if (bodyAnim != nullptr) {
		bodyAnim->LeftHandLocation = Player->LeftController->GetComponentLocation();
		bodyAnim->LeftHandRotation = Player->LeftController->GetComponentRotation();

		bodyAnim->RightHandLocation = Player->RightController->GetComponentLocation();
		bodyAnim->RightHandRotation = Player->RightController->GetComponentRotation();

		bodyAnim->HeadLocation = Player->CameraComp->GetComponentLocation();
		bodyAnim->HeadRotation = Player->CameraComp->GetComponentRotation();


		bodyAnim->LeftFootLocation = Player->LeftController->GetComponentLocation();
		bodyAnim->LeftFootRotation = Player->LeftController->GetComponentRotation();

		bodyAnim->RightFootLocation = Player->RightController->GetComponentLocation();
		bodyAnim->RightFootRotation = Player->RightController->GetComponentRotation();
	}



}

