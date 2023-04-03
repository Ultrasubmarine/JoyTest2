// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionKeyView.h"
#include "JoyTest/JoyTestCharacter.h"

#include "Runtime/UMG/Public/Components/PanelWidget.h"

void UActionKeyView::Initialize(AJoyTestCharacter* character)
{
	character->OnChangePickUpAbility.AddDynamic(this, &UActionKeyView::SetVisible);
}

void UActionKeyView::SetVisible(bool visible)
{
	overlay->SetVisibility(visible ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}
