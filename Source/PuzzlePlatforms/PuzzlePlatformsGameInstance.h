// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public: 

	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenuWidget();

	UFUNCTION(Exec, BlueprintCallable)
	void InGameLoadMenu();

	UFUNCTION(Exec)
	void Host() override;

	UFUNCTION(Exec)
	void Join(const FString& Address) override;

	virtual void LoadMainMenu() override;


private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MenuClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> EscapeMenuClass;


	class UMainMenu* Menu = nullptr;

	class UReturnToMenu* EscapeMenu = nullptr;

	// For delegates
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySession(FName SessionName, bool Success);

	void CreateSession();

	IOnlineSessionPtr SessionInterface;
	
	
	
	
};
