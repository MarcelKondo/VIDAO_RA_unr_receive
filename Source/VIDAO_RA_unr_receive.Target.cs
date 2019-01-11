// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class VIDAO_RA_unr_receiveTarget : TargetRules
{
	public VIDAO_RA_unr_receiveTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "VIDAO_RA_unr_receive" } );
	}
}
