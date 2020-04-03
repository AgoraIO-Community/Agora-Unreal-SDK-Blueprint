//  Copyright (c) 2019 Agora.io. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AgoraVideoCallTarget : TargetRules
{
	public AgoraVideoCallTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "AgoraVideoCall" } );
	}
}
