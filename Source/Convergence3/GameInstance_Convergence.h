// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_Convergence.generated.h"

UCLASS()
class CONVERGENCE3_API UGameInstance_Convergence : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameInstance_Convergence(const FObjectInitializer & ObjectInitializer);

	UFUNCTION(Exec)
	void Host();
	
	UFUNCTION(Exec)
	void Join(const FString& Address);

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

private:
	TSubclassOf<class UUserWidget> MenuClass;
};
