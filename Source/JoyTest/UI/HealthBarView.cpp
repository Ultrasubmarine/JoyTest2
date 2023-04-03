// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarView.h"


void UHealthBarView::UpdateBar(int fullValue, int currValue)
{
	healthBar->SetPercent(static_cast<float>(currValue) / fullValue);
}