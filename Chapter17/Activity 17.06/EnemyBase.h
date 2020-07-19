// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperSideScrollerCharacter.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPERSIDESCROLLER_API AEnemyBase : public ASuperSideScrollerCharacter
{
	GENERATED_BODY()

public:

	AEnemyBase();

	void DestroyEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DeathSound;

private:

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};