// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformsGameMode.h"
#include "PuzzlePlatformsCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzlePlatformsGameMode::APuzzlePlatformsGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APuzzlePlatformsGameMode::BroadcastDelegateEvent()
{
	float ValueToBroadcast = 1.0f;
	// This is when your event will fire and all subscribed actors will receive some data.
	OnSomethingHappened.Broadcast(ValueToBroadcast);
}

void APuzzlePlatformsGameMode::BindToDelegate()
{
	APuzzlePlatformsGameMode* GameMode = Cast<APuzzlePlatformsGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		// You subscribe some function to this delegate
		// Keep in mind that function parameters must be the same as the delegate parameters!
		GameMode->OnSomethingHappened.AddDynamic(this, &APuzzlePlatformsGameMode::OnDelegateEvent);
	}
}

void APuzzlePlatformsGameMode::OnDelegateEvent(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Data from delegate: %f"), Value);
}
