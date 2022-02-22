// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Kismet/GameplayStatics.h"


UCustomGameInstance::UCustomGameInstance()
{
	bDedi = false;
}

void UCustomGameInstance::Init()
{
	Super::Init();
	
	if(IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		SessionInterface = SubSystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCustomGameInstance::OnCreateSession);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UCustomGameInstance::OnJoinSession);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCustomGameInstance::OnFindSessions);
		}
		if(IsRunningDedicatedServer())
		{
			UE_LOG(LogTemp, Error, TEXT("Running as Dedicated!!!"));
			bDedi = true;
			CreateServer();
		}else
		{
			bDedi = false;
		}
	}
	
}

void UCustomGameInstance::Shutdown()
{
	Super::Shutdown();

	SessionInterface->DestroySession(FName("MySession_Test"));
	
}

void UCustomGameInstance::OnCreateSession(FName SessionName, bool bSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSession: %d"), bSuccess);
	if(bSuccess)
	{
		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void UCustomGameInstance::OnJoinSession(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSession"));

	if(APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {

		FString Address;
		SessionInterface->GetResolvedConnectString(SessionName, Address);
		
		PC->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UCustomGameInstance::OnFindSessions(bool bSuccess)
{
	if(bSuccess)
	{
		TArray<FOnlineSessionSearchResult> Results = SessionSearch->SearchResults;
		
		UE_LOG(LogTemp, Warning, TEXT("OnFindSessions: %d"), Results.Num());
		
		UE_LOG(LogTemp, Warning, TEXT("ASDASDSADSADASDSADSADASDSADASDASDASDDS"));
		if(Results.Num())
		{
			
			bool bsuc = SessionInterface->JoinSession(0, FName("MySession_Test"), Results[0]);

			UE_LOG(LogTemp, Error, TEXT("SUCCCECCSCSDAA: %d"), bsuc);
		}
		
	}
}

void UCustomGameInstance::CreateServer()
{
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = bDedi; //Change this later;
	SessionSettings.bIsLANMatch = false;
	SessionSettings.bUsesPresence = !bDedi; //for listen server, this is true, for dedicated it should be false;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPublicConnections = 7;
	
	SessionInterface->CreateSession(0, FName("MySession_Test"), SessionSettings);
}

void UCustomGameInstance::JoinServer()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->bIsLanQuery = false;
	SessionSearch->MaxSearchResults = 10000;

	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}


