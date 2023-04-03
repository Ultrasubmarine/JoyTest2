// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "HealthItem.generated.h"

/**
 * 
 */
UCLASS()
class JOYTEST_API UHealthItem : public UItem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int healthValue;

public:

	UFUNCTION(BlueprintCallable)
	int GetHealthValue() { return healthValue; };
};
