// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "ServerLineWidget.h"
#include "ScrollBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"



void UMainMenu::AddServerToList(FString ServerName)
{
	if (ServerLineBP)
	{
		UServerLineWidget* ServerLine = Cast<UServerLineWidget>(CreateWidget(this, ServerLineBP));
		if (ServerLine)
		{
			ServerLine->Setup(ServerName);
			ServerList->AddChild(ServerLine);
		}
	}
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success) return false;

	// Setup
	if (!ensure(Host != nullptr)) return false;
	Host->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(Join != nullptr)) return false;
	Join->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::ReturnToMainMenu);

	if (!ensure(ConfirmJoinButton != nullptr)) return false;
	ConfirmJoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::Quit);

	return true;
}






void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
	UE_LOG(LogTemp, Warning, TEXT("Hosting server"));
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
		{
		FString Address = ""; //ServerIP->GetText().ToString();
			MenuInterface->Join(Address);
		}
}

void UMainMenu::OpenJoinMenu()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::ReturnToMainMenu()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::Quit()
{
	GetOwningPlayer()->ConsoleCommand("quit");
}