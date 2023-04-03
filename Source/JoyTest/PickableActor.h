// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "PickableActor.generated.h"

class UItem;

UCLASS()
class JOYTEST_API APickableActor : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	APickableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItem> Item;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(Blueprintcallable)
	TSubclassOf<UItem> GetItem() { return Item; };

};
