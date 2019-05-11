// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerLineWidget.h"
#include "Button.h"
#include "TextBlock.h"

bool UServerLineWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	// Setup
	if (!ensure(ServerButton != nullptr)) return false;
	ServerButton->OnClicked.AddDynamic(this, &UServerLineWidget::JoinServer);

	return true;
}



void UServerLineWidget::Setup(const FString ServerName)
{
	if (!ensure(ServerText != nullptr)) return;

	ServerText->SetText(FText::FromString(ServerName));

}

void UServerLineWidget::JoinServer()
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to join server"));
}
