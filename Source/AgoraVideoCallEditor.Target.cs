//  Copyright (c) 2019 Agora.io. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AgoraVideoCallEditorTarget : TargetRules
{
    public AgoraVideoCallEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;

        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange(new string[] { "AgoraVideoCall" });
    }
}
