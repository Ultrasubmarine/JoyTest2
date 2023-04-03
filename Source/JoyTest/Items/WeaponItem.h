// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "JoyTest/WeaponActor.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class JOYTEST_API UWeaponItem : public UItem
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeaponActor> actor;
	
public:
	UFUNCTION()
	TSubclassOf<AWeaponActor> GetWeaponActor() { return actor; };

};
