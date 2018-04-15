// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance_Convergence.h"
#include "Engine/Engine.h"

void UGameInstance_Convergence::Host()
{
	GLog->Log(TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	World->ServerTravel("/Game/Level_Game?listen");

}

void UGameInstance_Convergence::Join(const FString & Address)
{
	GLog->Log(TEXT("Joining"));
}
