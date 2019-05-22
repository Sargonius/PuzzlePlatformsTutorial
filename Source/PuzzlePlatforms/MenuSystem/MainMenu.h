// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:

	UMainMenu();

	UFUNCTION(BlueprintCallable)
	void AddServerToList(FString ServerName);

	UFUNCTION(BlueprintCallable)
	void ClearServerList();

	void SelectIndex(uint32 Index);

	UPROPERTY(meta = (BindWidget))
	class UButton* Host; 

	UPROPERTY(meta = (BindWidget))
	class UButton* Join;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmJoinButton;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* JoinMenu;

// 	UPROPERTY(meta = (BindWidget))
// 	class UEditableTextBox* ServerIP; 

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* ServerList;

protected:
	virtual bool Initialize();

	UFUNCTION()
	void HostServer();

	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void ReturnToMainMenu();

	UFUNCTION()
		void Quit();

	UPROPERTY()
	TSubclassOf<class UUserWidget> ServerLineBP;

	TOptional<uint32> SelectedIndex;


	
	
};
