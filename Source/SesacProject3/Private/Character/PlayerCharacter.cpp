

#include "Character/PlayerCharacter.h"

#include "MotionControllerComponent.h"
#include "NavigationSystemTypes.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "DSP/Chorus.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon/WeaponBase.h"

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
	LeftLog->SetRelativeScale3D(FVector(0.5));
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
	RightLog->SetRelativeScale3D(FVector(0.5));
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

#pragma region (CurrentLoc - OldLoc) / DeltaTime
	 // 과거 위치와 현재 위치가 같을 경우, 과거 위치의 값을 구하지 않음
	if (OldLocation != CurrentLocation)
	{
		OldLocation = RightController->GetComponentLocation();
	}
	CurrentLocation = RightController->GetComponentLocation();

	// 속력 = 이동 거리 / 걸린 시간
	FVector Velocity = (OldLocation - CurrentLocation) / DeltaTime;
	
	// Velocity의 XYZ 값 중 가장 큰 값만 사용하기 위해 MaxValue 변수를 선언 
	int MaxValue = static_cast<int>(FMath::Max3(Velocity.X,Velocity.Y, Velocity.Z));
	
	// Set RightLog Text
	RightLog->SetText(FText::FromString(FString::Printf(TEXT("Velocity : %d"), MaxValue)));
	
	// MaxValue 값이 100 이상, bISAttack이 false일 경우, StartAttack()을 실행
	if (MaxValue > 100 && bIsAttack == false && bIsDefence == false)
	{
		StartAttack();
	}
	else // 아닐 경우 StopAttack()을 실행
	{
		StopAttack();
	}
#pragma endregion

#pragma region 내각 사용
	/*if (OldLocation != CurrentLocation)
	{
		OldLocation = RightController->GetUpVector();
	}
	else
	{
		CurrentLocation = RightController->GetUpVector();
	}
	
	// 내각을 구해서 45도 이상이면 공격으로 판정
	float DotProduct = FVector::DotProduct(OldLocation, CurrentLocation);

	// Set RightLog Text
	RightLog->SetText(FText::FromString(FString::Printf(TEXT("%f"), DotProduct)));
	
	if (DotProduct > 45 && bIsAttack == false && bIsDefence == false)
	{
		StartAttack();
	}
	else
	{
		StopAttack();
	}*/
#pragma endregion

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(RightTrigger, ETriggerEvent::Triggered, this, &APlayerCharacter::StartDefence);
		EnhancedInputComponent->BindAction(RightTrigger, ETriggerEvent::Completed, this, &APlayerCharacter::StopDefence);
	}
}

void APlayerCharacter::StartAttack()
{
	bIsAttack = true;
	if (Weapon)
	{
		Weapon->SetAttackMode(true);
	}
	IsAttack();
}

void APlayerCharacter::StopAttack()
{
	bIsAttack = false;
	if (Weapon)
	{
		Weapon->SetAttackMode(false);
	}
	IsAttack();
}

bool APlayerCharacter::IsAttack()
{
	LeftLog->SetText(FText::FromString(bIsAttack ? TEXT("true") : TEXT("false")));
	return bIsAttack;
}

void APlayerCharacter::StartDefence()
{
	bIsDefence = true;
}

void APlayerCharacter::StopDefence()
{
	bIsDefence = false;
}

void APlayerCharacter::StartStun()
{
	Super::StartStun();

	// Controller Disable
	// bIsStun 동안 상태 Display(HUD 빨갛게 오버레이 또는 헤롱헤롱(?), 삐약삐약(?))
}

void APlayerCharacter::StopStun()
{
	Super::StopStun();

	// Controller Enable
}

FVector APlayerCharacter::GetAttackAngle()
{
	FVector AttackAngle = CurrentLocation - OldLocation;
	return AttackAngle;
}
