// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "GameInstance_Convergence.generated.h"

UCLASS()
class CONVERGENCE3_API UGameInstance_Convergence : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstance_Convergence(const FObjectInitializer & ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void Host();
	
	UFUNCTION(BlueprintCallable)
	void Join(const FString& Address);

	UFUNCTION(BlueprintCallable)
	void LoadMenuWidget();

private:
	TSubclassOf<class UUserWidget> MenuClass;

	IOnlineSessionPtr SessionInterface;

	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnSessionDestroy(FName SessionName, bool Success);

	void CreateSession();
};
