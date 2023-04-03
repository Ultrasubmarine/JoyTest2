// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JoyTest/ItemType.h"
#include "Item.generated.h"

/**
 * 
 */


UCLASS(Blueprintable, BlueprintType)
class JOYTEST_API UItem : public UObject
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ItemType type;

public:
	ItemType GetType() { return type; };
};
