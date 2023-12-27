// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class AWeaponBase;

UCLASS()
class SESACPROJECT3_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* LeftHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* RightHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	AWeaponBase* Weapon;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySettings|Components", meta = (AllowPrivateAccess = "true"))
	// EMainHand MainHand;

	// 공격 성공시 전진, 피격시 넉백 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Value", meta = (AllowPrivateAccess = "true"))
	float AttackSuccessDistance = 50.f;

	// 방어 성공시 전진, 공격 실패시 넉백 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Value", meta = (AllowPrivateAccess = "true"))
	float DefenceSuccessDistance = -25.f;
	
	// Vertical 이동 스피드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Value", meta = (AllowPrivateAccess = "true"))
	float VerticalInterpSpeed = 5.0f;

	// Horizontal 이동 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Value", meta = (AllowPrivateAccess = "true"))
	float MoveHorizontalDistance = 50.f;

	// Horizontal 이동 스피드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Value", meta = (AllowPrivateAccess = "true"))
	float MoveHorizontalInterpSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Value", meta = (AllowPrivateAccess = "true"))
	float StunTime = 1.0f;
	
	bool bIsStun = false;

	bool bIsDefence = false;

	FTimerHandle StunTimerHandler;

public:
	// 방어 상태를 반환하는 함수
	virtual bool IsDefence();

	// 메인 핸드의 각도를 반환하는 함수
	float GetMainHandAngle();

	// 서브 핸드의 각도를 반환하는 함수(DualBlade의 경우 사용)
	float GetSubHandAngle();

	// 현재 모션이 공격인지 판단하여 반환하는 함수
	virtual bool IsAttack();

	// 공격 성공 시, 전진
	void SuccessAttack();
	
	// 피격 시, 넉백
	void ReceiveDamage();
	
	// 방어 성공 시, 전진
	void SuccessDefence();
	
	// 공격 실패 시(상대 방어 시) 호출, 스턴 + 넉백
	void FailAttack();

	// Vertical 이동(전진, 넉백)
	void MoveVertical(float VerticalDistance);

	// 방어 상태일 경우, 검이 향하는 방향으로 Horizontal 이동
	void MoveHorizontal();

	// 스턴 발생 함수
	virtual void StartStun();

	virtual void StopStun();
	
	virtual AWeaponBase* GetWeapon();

	virtual FVector GetAttackAngle();
};
