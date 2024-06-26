// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class TUTORIAL_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Dodgeball, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float Damage = 34.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// FORCEINLINE : Must implement in header file
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const {
		return ProjectileMovement;
	}

};
