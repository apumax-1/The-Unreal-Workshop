// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

void AEnemyBase::DestroyEnemy()
{
	Destroy();
}
