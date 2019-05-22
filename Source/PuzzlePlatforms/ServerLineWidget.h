// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerLineWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerLineWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void Setup(const FString ServerName, uint32 Index);

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerText;

	class UMainMenu* MainMenuReference;

	uint32 Index;

	virtual bool Initialize();

	UFUNCTION()
	void JoinServer();

	
};
