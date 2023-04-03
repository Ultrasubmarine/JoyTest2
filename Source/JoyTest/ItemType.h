// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "ItemType.generated.h"


UENUM(BlueprintType)
enum class ItemType : uint8
{
	ITEM_NONE =0 UMETA(DisplayName = "None"),
	ITEM_GUN = 1 UMETA(DisplayName = "Gun"),
	ITEM_HEALTH = 2 UMETA(DisplayName = "Health"),
};