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
	UFUNCTION()
	void Setup(const FString ServerName);

	UPROPERTY(meta = (BindWidget))
	class UButton* ServerButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerText;

	virtual bool Initialize();

	UFUNCTION()
	void JoinServer();

	
};
