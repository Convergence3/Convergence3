// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance_Convergence.h"
#include "Engine/Engine.h"
#include "OnlineSubsystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"


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
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{

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
