// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/RoundBoxActor.h"

#include "InterchangeResult.h"
#include "MyGameStateBase.h"
#include "Character/CharacterBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ARoundBoxActor::ARoundBoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
}

// Called when the game starts or when spawned
void ARoundBoxActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARoundBoxActor::OnBoxComponentBeginOverlap);
}

// Called every frame
void ARoundBoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoundBoxActor::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// UE_LOG(LogTemp, Warning, TEXT("ARoundBoxActor::OnBoxComponentBeginOverlap) Overlapped Actor : %s"), *OtherActor->GetActorNameOrLabel());
	if (ACharacterBase* Character = Cast<ACharacterBase>(OtherActor))
	{
		GetWorld()->GetGameState<AMyGameStateBase>()->SetLoseCharacter(Character);
	}
}