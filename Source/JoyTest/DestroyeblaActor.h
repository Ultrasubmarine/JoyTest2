// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoyTestCharacter.h" // for 
#include "DestroyeblaActor.generated.h"




UCLASS()
class JOYTEST_API ADestroyeblaActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyeblaActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int health = 100;

	int healthCurrent;

public:	

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FChangeHealth OnChangeHealth;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Damage(float value);
};
