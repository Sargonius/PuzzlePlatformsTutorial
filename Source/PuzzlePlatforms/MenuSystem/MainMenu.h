// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMenuInterface(IMenuInterface* MenuInterface);
	
	UPROPERTY(meta = (BindWidget))
	class UButton* Host; 

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

protected:
	virtual bool Initialize();

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	IMenuInterface* MenuInterface;
	
	
	
};