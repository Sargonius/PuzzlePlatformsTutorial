// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
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
	void Join(uint32 Index) override;

	virtual void LoadMainMenu() override;

	UFUNCTION(Exec)
	void RefreshServerList() override;


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
	void OnFindSessionComplete(bool Success);

	void CreateSession();

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	IOnlineSessionPtr SessionInterface;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;
	
	
	
	
};
