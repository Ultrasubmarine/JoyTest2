// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Containers/List.h"
#include "DamageZone.generated.h"


class AJoyTestCharacter;

USTRUCT()
struct FDamagedCharacter
{
	GENERATED_USTRUCT_BODY()

	AJoyTestCharacter* Character;
	float LastDamageTime;
};


UCLASS()
class JOYTEST_API ADamageZone : public AActor
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	ADamageZone();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickable")
	UBoxComponent* PickableCapsule;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TMap<AJoyTestCharacter*, FDamagedCharacter> _damagedCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float delayDelta = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int damageValue = 10;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bfromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Damage(FDamagedCharacter& c);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
