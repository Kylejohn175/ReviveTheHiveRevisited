// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GlobalGameJam2020Target : TargetRules
{
	public GlobalGameJam2020Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "GlobalGameJam2020" } );
	}
}
