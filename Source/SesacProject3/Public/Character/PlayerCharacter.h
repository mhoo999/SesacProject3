
#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "InputAction.h"
#include "PlayerCharacter.generated.h"

class UTextRenderComponent;
class UMotionControllerComponent;
class UCameraComponent;
class UInputMappingContext;

UCLASS()
class SESACPROJECT3_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HMDComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* LeftController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* RightController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* LeftLog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* RightLog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	UInputAction* RightTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Inputs", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IMC;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Inputs", meta = (AllowPrivateAccess = "true"))
	float AttackSuccessValue = -1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Inputs", meta = (AllowPrivateAccess = "true"))
	float AttackTimer = 0.3f;

	float CurrentTime = 0;
	
	FVector OldLocation;
	FVector CurrentLocation;
	
	bool bIsAttack = false;

public:
	void StartAttack();
	void StopAttack();
	virtual bool IsAttack() override;

	void StartDefence();
	void StopDefence();
	virtual bool IsDefence() override;
	
	virtual void StartStun() override;
	virtual void StopStun() override;

	virtual FVector GetAttackAngle() override;
};
