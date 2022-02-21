// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SESSIONHANDLINGSTEAM_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UCustomGameInstance();

	bool bDedi;

protected:

	virtual void Init() override;
	virtual void Shutdown() override;

	IOnlineSessionPtr SessionInterface;

	void OnCreateSession(FName SessionName, bool bSuccess);
	
	void OnJoinSession(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	void OnFindSessions(bool bSuccess);

	TSharedPtr<FOnlineSessionSearch> SessionSearch;

public:

	UFUNCTION(BlueprintCallable)
		void CreateServer();

	UFUNCTION(BlueprintCallable)
		void JoinServer();
	
};
