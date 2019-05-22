// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerLineWidget.h"
#include "Button.h"
#include "TextBlock.h"
#include "MenuSystem\MainMenu.h"

bool UServerLineWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	// Setup
	if (!ensure(ServerButton != nullptr)) return false;
	ServerButton->OnClicked.AddDynamic(this, &UServerLineWidget::JoinServer);

	return true;
}



void UServerLineWidget::Setup(const FString ServerName, uint32 IndexToSet)
{
	if (!ensure(ServerText != nullptr)) return;

	ServerText->SetText(FText::FromString(ServerName));
	Index = IndexToSet;
}

void UServerLineWidget::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to join server"));
	if (MainMenuReference)
	{
		MainMenuReference->SelectIndex(Index);
	}
}
