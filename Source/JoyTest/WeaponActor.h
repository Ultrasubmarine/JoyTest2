// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class JOYTEST_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	float fireDelay = 0.2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	int damage = 10;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Fire(FVector purpose);


	UFUNCTION(BlueprintCallable)
	float GetDelay() { return fireDelay; };

};
