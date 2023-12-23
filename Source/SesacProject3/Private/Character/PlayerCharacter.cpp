

#include "Character/PlayerCharacter.h"

#include "MotionControllerComponent.h"
#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "DSP/Chorus.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(RootComponent);

	HMDComp = CreateDefaultSubobject<UStaticMeshComponent>("HMDComp");
	HMDComp->SetupAttachment(CameraComp);

	LeftController = CreateDefaultSubobject<UMotionControllerComponent>("LeftController");
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetRelativeLocation(FVector(50, -30, -10));
	LeftController->SetTrackingMotionSource(FName("Left"));

	LeftHandMesh->SetupAttachment(LeftController);
	LeftHandMesh->SetRelativeRotation(FRotator(-50, 180, 90));
	
	LeftLog = CreateDefaultSubobject<UTextRenderComponent>("LeftLog");
	LeftLog->SetupAttachment(LeftHandMesh);
	LeftLog->SetRelativeLocation(FVector(-20, 10, 0));
	LeftLog->SetRelativeRotation(FRotator(0, -90, -90));
	LeftLog->SetHorizontalAlignment(EHTA_Center);
	LeftLog->SetVerticalAlignment(EVRTA_TextCenter);
	LeftLog->SetTextRenderColor(FColor(255, 255, 0));
	
	RightController = CreateDefaultSubobject<UMotionControllerComponent>("RightController");
	RightController->SetupAttachment(RootComponent);
	RightController->SetRelativeLocation(FVector(50, 30, -10));
	RightController->SetTrackingMotionSource(FName("Right"));

	RightHandMesh->SetupAttachment(RightController);
	RightHandMesh->SetRelativeRotation(FRotator(50, 0, 90));

	RightLog = CreateDefaultSubobject<UTextRenderComponent>("RightLog");
	RightLog->SetupAttachment(RightHandMesh);
	RightLog->SetRelativeLocation(FVector(20, 10, 0));
	RightLog->SetRelativeRotation(FRotator(0, -90, 90));
	RightLog->SetHorizontalAlignment(EHTA_Center);
	RightLog->SetVerticalAlignment(EVRTA_TextCenter);
	RightLog->SetTextRenderColor(FColor(255, 255, 0));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Velocity = RightController->GetComponentVelocity();
	UE_LOG(LogTemp, Warning, TEXT("Velocity : %s"), *Velocity.ToString());
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool APlayerCharacter::IsAttack()
{
	return Super::IsAttack();
	
}

