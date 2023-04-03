// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyeblaActor.h"

// Sets default values
ADestroyeblaActor::ADestroyeblaActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestroyeblaActor::BeginPlay()
{
	Super::BeginPlay();
	healthCurrent = health;
	
}

// Called every frame
void ADestroyeblaActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyeblaActor::Damage(float value)
{

	healthCurrent -= value;

	if (healthCurrent <= 0)
	{
		healthCurrent = 0;
		Destroy();
		return;
	}

	OnChangeHealth.Broadcast(health, healthCurrent);
}

