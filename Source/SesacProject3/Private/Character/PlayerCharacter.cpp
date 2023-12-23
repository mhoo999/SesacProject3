

#include "Character/PlayerCharacter.h"

#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"

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
	LeftController->SetTrackingMotionSource(FName("Left"));

	LeftHandMesh->SetupAttachment(LeftController);
	
	RightController = CreateDefaultSubobject<UMotionControllerComponent>("RightController");
	RightController->SetupAttachment(RootComponent);
	RightController->SetTrackingMotionSource(FName("Right"));

	RightHandMesh->SetupAttachment(RightController);
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

