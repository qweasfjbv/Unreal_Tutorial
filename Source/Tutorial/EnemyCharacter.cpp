// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DodgeballFunctionLibrary.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("SightSource"));
	SightSource->SetupAttachment(RootComponent);
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
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if (bCanSeePlayer != bPreviousCanSeePlayer) {
		if (bCanSeePlayer){	// start to throw dodgeball
			GetWorldTimerManager().SetTimer(ThrowTimerHandle,
				this,
				&AEnemyCharacter::ThrowDodgeball, ThrowingInterval,
				true,
				ThrowingDelay);
		}
		else {		// stop throwing dodgeball
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	bPreviousCanSeePlayer = bCanSeePlayer;

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemyCharacter::LookAtActor(AActor* TargetActor) {
	if (TargetActor == nullptr) return false;

	const TArray<const AActor*> IgnoreActors = { this, TargetActor };

	if (UDodgeballFunctionLibrary::CanSeeActor(GetWorld(),
		SightSource->GetComponentLocation(),
		TargetActor,
		IgnoreActors)) {

		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

		SetActorRotation(LookAtRotation);
		return true;
	}

	return false;
}

void AEnemyCharacter::ThrowDodgeball() {
	if (DodgeballClass == nullptr) return;

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.f;

	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);

	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
	
	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);
	ProjectileMovement = Projectile->GetProjectileMovement();
	ProjectileMovement->InitialSpeed = 2200.f;
	Projectile->FinishSpawning(SpawnTransform);

	//GetWorld()->SpawnActor<ADodgeballProjectile>(DodgeballClass, SpawnLocation, GetActorRotation());
}