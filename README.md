# AgoraVideoCall

The Agora Video Call is a demo app that will help you get video chat integrated directly into your Unreal Engine applications using the AgoraPlugin, that wraps Agora Video SDK.

With this sample app, you can:

- Join / leave channel
- Mute / unmute audio
- Enable / disable video
- Switch camera
- Setup resolution and frame rate 

Developed with Unreal Engine 4.23

There are two implementations of Agora Video Call demo application:
1) [C++ based](https://github.com/AgoraIO-Community/Agora-Unreal-SDK-CPP)
2) Blueprints based.

For step-by-step instruction on building the video-chat functionality from scratch, see the GUIDE.md files in either project.

Agora plugin is implemented as separate module, but is already included in the sample project.  
[download the plugin here](https://gitlab.nixdev.co/agora.io/agora.io-ue-plugin) and add it's contents to Plugins/AgoraPlugin for each project if you are starting from scratch.

Download the project with command `git clone --recursive todo::link_to_the_repo`.

## Opening the Project
When you first open the AgoraVideoCall.uproject, you will receive a message saying, "Missing Agora Video Call Modules", click "Yes" and the project should open smoothly. 
If you are still having issues, right click the .uproject file, and select "Generate XCode Project" (or the PC equivalent), and rebuild the project.

## Building and running the App

Open AgoraVideoCall.uproject with Unreal Editor( version no less than 4.23 ).

To package the project:

1) File->Package Project->Windows->Windows(64-bit) then select a folder where you want to package and wait for result.

![Alt text](ReadMeImages/HowToPackageProject.png?raw=true "PackageProject")
![Alt text](ReadMeImages/HowToPackageProjectMac.png?raw=true "PackageProject")

2) Now need to package the plugin for PC. 

For MacOS it isn't necessary, skip this step.

Edit->Plugins-> Skip Built-In plugins and scroll down to "Project", click on "Other" to find "AgoraPlugin", then "Package", and select the folder inside the packaged project:
(Packaged project dir)/WindowsNoEditor/AgoraVideoCall/Plugins/AgoraPlugin/.

![Alt text](ReadMeImages/HowToPackagePlugin.png?raw=true "PackagePlugin")

3) Now you can find executable file of the demo App in the folder selected on step (1) and run the App.

## Supported platforms

Windows 64-bit

Mac

## Use the plugin in your project
The plugin is already included in: [your_project]Plugins/AgoraPlugin
If making a new project from scratch:

1. Add plugin dependency into [your_project]/Source/[project_name]/[project_name].Build.cs, Private Dependencies section

`PrivateDependencyModuleNames.AddRange(new string[] { "AgoraPlugin", "AgoraBlueprintable" });`

2. Open Unreal Project, go to **Edit->Plugins**. Find category **Project->Other** and make sure plugin is enabled.

![Enable Plugin](ReadMeImages/2020-03-12_13-26-59.png)

## Connect Us

- You can find full API document at [Document Center](https://docs.agora.io/en/)

## Mac Build Permissions

Add the following permissions in the info.plist file for device access:
1. Build the project for Mac
2. Right click [your_project_build_name].app and select "Show Package Contents"
3. Open the "Info.plist" file 
4. Add: "Privacy - Camera Usage Description" and "Privacy - Microphone Usage Description" as two new entries

