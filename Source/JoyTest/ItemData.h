// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
//#include "UObject/NoExportTypes.h"

#include "ItemType.h"

#include "ItemData.generated.h"

class UStatickMesh;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemData()
	{
		ID = 666;
		Type = ItemType::ITEM_GUN;
	//	FText Name;

		StaticMesh = nullptr;
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;


};
