// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActor(PlayerCharacter);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor)const {
	if (TargetActor == nullptr) {
		return false;
	}

	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = TargetActor->GetActorLocation();

	// Channel needed to use Trace
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;

	// Add Ignored Actor
	// cuz linetrace start from center
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(TargetActor);

	
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	// DEBUG
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	return !Hit.bBlockingHit;
}

void AEnemyCharacter::LookAtActor(AActor* TargetActor) {
	if (TargetActor == nullptr) return;

	if (CanSeeActor(TargetActor)) {
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		SetActorRotation(LookAtRotation);
	}
}