// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance_Convergence.h"
#include "Engine/Engine.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

const static FName SESSION_NAME = TEXT("SessionGame");

UGameInstance_Convergence::UGameInstance_Convergence(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Menu/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr))return;
	MenuClass = MenuBPClass.Class;
}

void UGameInstance_Convergence::Init()
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGameInstance_Convergence::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UGameInstance_Convergence::OnSessionDestroy);
		}
	}
}

void UGameInstance_Convergence::LoadMenuWidget()
{
	if (!ensure(MenuClass != nullptr))return;
	UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
	if (!ensure(Menu != nullptr))return;
	Menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))return;
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UGameInstance_Convergence::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
	else {
		GLog->Log(TEXT("Session Interface not valid"));
	}
}

void UGameInstance_Convergence::OnSessionDestroy(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UGameInstance_Convergence::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings Settings;
		SessionInterface->CreateSession(0, SESSION_NAME, Settings);
	}
}

void UGameInstance_Convergence::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success) {
		GLog->Log(TEXT("!Hosting"));
		return;
	}
	GLog->Log(TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr))return;

	World->ServerTravel("/Game/Level_Game?listen");

}

void UGameInstance_Convergence::Join(const FString & Address)
{
	GLog->Log(TEXT("Joining"));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr))return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
