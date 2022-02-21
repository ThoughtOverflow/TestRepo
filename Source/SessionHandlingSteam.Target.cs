// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SessionHandlingSteamTarget : TargetRules
{
	public SessionHandlingSteamTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("SessionHandlingSteam");

		bUsesSteam = true;
		GlobalDefinitions.Add("UE4_PROJECT_STEAMPRODUCTNAME=\"spacewar\"");
		GlobalDefinitions.Add("UE4_PROJECT_STEAMGAMEDIR=\"spacewar\"");
		GlobalDefinitions.Add("UE4_PROJECT_STEAMGAMEDESC=\"AWESOMEPLZWORKDUDE\"");
		GlobalDefinitions.Add("UE4_PROJECT_STEAMSHIPPINGID=\"480\"");
		
	}
}
