// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Collectable.h"
#include "SuperSideScroller_Player.h"
//#include "Components/StaticMeshComponent.h"

void APickableActor_Collectable::BeginPlay()
{
	Super::BeginPlay();
	//MeshComp->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, 300.0f), false);
}

void APickableActor_Collectable::PlayerPickedUp(class ASuperSideScroller_Player* Player)
{
	Player->IncrementNumberofCollectables(CollectableValue);
	Super::PlayerPickedUp(Player);
}