// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "MenuSystem/MenuWidget.h"

#include "MenuSystem/MainMenu.h"

const static FName SESSION_NAME = TEXT("My Session Game");

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/BPW_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;

	MenuClass = MenuBPClass.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> EscapeMenuBPClass(TEXT("/Game/MenuSystem/BPW_EscapeMenu"));
	if (!ensure(EscapeMenuBPClass.Class != nullptr)) return;

	EscapeMenuClass = EscapeMenuBPClass.Class;
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
	IOnlineSubsystem* OnlineSubsystemRef = IOnlineSubsystem::Get();
	if (OnlineSubsystemRef != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem: %s"), *OnlineSubsystemRef->GetSubsystemName().ToString());
		SessionInterface = OnlineSubsystemRef->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Session!"));
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySession);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OnlineSubsystem is NULL!"));
	}
}

void UPuzzlePlatformsGameInstance::LoadMenuWidget()
{
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->Setup();

	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
	if (!ensure(EscapeMenuClass != nullptr)) return;

	UMenuWidget* MenuWidget = CreateWidget<UMenuWidget>(this, EscapeMenuClass);

	if (!ensure(MenuWidget != nullptr)) return;

	MenuWidget->Setup();

	MenuWidget->SetMenuInterface(this);

}

void UPuzzlePlatformsGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not create session"));
		return;
	}

	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 3, FColor::Green, TEXT("Host"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Static/Maps/Game?listen");
}

void UPuzzlePlatformsGameInstance::OnDestroySession(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UPuzzlePlatformsGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid())
	{
		for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("Session: %s"), *Result.GetSessionIdStr());
			if (Menu)
			{
				Menu->AddServerToList(Result.GetSessionIdStr());
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("Find session finished"));
	}
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;

		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 3, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}


void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/MenuSystem/MainMenu", ETravelType::TRAVEL_Absolute);


}

void UPuzzlePlatformsGameInstance::RefreshServerList()
{
	if (Menu)
	{
		Menu->ClearServerList();
	}

	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		UE_LOG(LogTemp, Warning, TEXT("Starting to find session"));
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

