// Fill out your copyright notice in the Description page of Project Settings.

#include "ReturnToMenu.h"
#include "Components/Button.h"

bool UReturnToMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	// Setup
	if (!ensure(ReturnToMenuButton != nullptr)) return false;
	ReturnToMenuButton->OnClicked.AddDynamic(this, &UReturnToMenu::LoadMenu);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UReturnToMenu::Teardown);

	return true;
}

void UReturnToMenu::LoadMenu()
{

}




