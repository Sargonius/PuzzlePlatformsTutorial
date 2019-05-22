// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuzzlePlatformsGameMode.generated.h"

// Above the class code!
// FOnSomethingHappened is the type, used below in class code
// ...DELEGATE_OneParam - there is one parameter in this delegate. 
// You can use TwoParams etc
// float - param type, Value - param name.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSomethingHappened, float, Value);

UCLASS(minimalapi)
class APuzzlePlatformsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APuzzlePlatformsGameMode();

	// Broadcast ("firing the event") example
	UFUNCTION(BlueprintCallable)
	void BroadcastDelegateEvent();

	// Bind (attach to event) example
	UFUNCTION(BlueprintCallable)
	void BindToDelegate();

	// Event handling example
	UFUNCTION(BlueprintCallable)
	void OnDelegateEvent(float Value);

	// That's our Delegate. You need to Broadcast it somewhere and Bind to it.
	UPROPERTY(BlueprintAssignable)
	FOnSomethingHappened OnSomethingHappened;
};



