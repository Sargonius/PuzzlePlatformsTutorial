// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "ReturnToMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UReturnToMenu : public UMenuWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnToMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CancelButton;

protected:
	virtual bool Initialize();

private:

	UFUNCTION()
	void CancelPressed();

	UFUNCTION()
	void LoadMenuPressed();
	
	
	
};
