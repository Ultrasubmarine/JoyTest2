// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarView.generated.h"

/**
 * 
 */
UCLASS()
class JOYTEST_API UHealthBarView : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* healthBar;

public:

	UFUNCTION(BlueprintCallable)
	void UpdateBar(int fullValue, int currValue);
};
