// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionKeyView.generated.h"

class UPanelWidget;
class UTextBlock;

class AJoyTestCharacter;

/**
 * 
 */
UCLASS()
class JOYTEST_API UActionKeyView : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* discriptionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* keyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UPanelWidget* overlay;

public:

	UFUNCTION(BlueprintCallable)
	virtual void  Initialize(AJoyTestCharacter* character); // widget link with PickUp delegat. for different delegates - override

	UFUNCTION()
	void SetVisible(bool visible);
};
