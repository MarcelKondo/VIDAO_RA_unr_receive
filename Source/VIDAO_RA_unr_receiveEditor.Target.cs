// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class VIDAO_RA_unr_receiveEditorTarget : TargetRules
{
	public VIDAO_RA_unr_receiveEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "VIDAO_RA_unr_receive" } );
	}
}
