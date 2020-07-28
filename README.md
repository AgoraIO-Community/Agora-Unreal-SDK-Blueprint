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
1) C++ based.
2) Blueprints based.

See [C++ Guide](C++\ Approach/GUIDE.md) and [Blueprints Guide](Blueprints\ Approach/GUIDE.md) for more info.

Agora plugin is implemented as separate module. Download the project with command `git clone --recursive todo::link_to_the_repo`,
or [download the plugin here](https://gitlab.nixdev.co/agora.io/agora.io-ue-plugin) and add it's contents to Plugins/AgoraPlugin for each project.

## Getting Started
The Agora Plugin must be downloaded, unzipped, and placed into the empty "Plugins" folder of your project's directory. 

[You can find the .zip file here](https://drive.google.com/file/d/1waEe7Hsh6Q-Fh4DhB8DbO3-EBeZ8lsSt/view?usp=sharing)

Drop the entire AgoraPlugin folder inside of the Plugins folder, and you are good to go!

## Building and running the App

Open AgoraVideoCall.uproject with Unreal Editor( version no less than 4.23 ).

To package the project:

1) File->Package Project->Windows->Windows(64-bit) then select a folder where you want to package and wait for result.

![Alt text](ReadMeImages/HowToPackageProject.png?raw=true "PackageProject")
![Alt text](ReadMeImages/HowToPackageProjectMac.png?raw=true "PackageProject")

2) Now need to package the plugin. 

For MacOS you don't need to do that. Just skip this step.

Edit->Plugins-> Skip Built-In plugins and scroll down to "Project", click on "Other" to find "AgoraPlugin", then "Package", and select the folder inside the packaged project:
(Packaged project dir)/WindowsNoEditor/AgoraVideoCall/Plugins/AgoraPlugin/.

![Alt text](ReadMeImages/HowToPackagePlugin.png?raw=true "PackagePlugin")

3) Now you can find executable file of the demo App in the folder selected on step (1) and run the App.

## Supported platforms

Windows 64-bit

Mac

iOS

## Use the plugin in your project

1. Copy the plugin to [your_project]/Plugins
2. Add plugin dependency into [your_project]/Source/[project_name]/[project_name].Build.cs, Private Dependencies section

`PrivateDependencyModuleNames.AddRange(new string[] { "AgoraPlugin", "AgoraBlueprintable" });`

3. Open Unreal Project, go to **Edit->Plugins**. Find category **Project->Other** and make sure plugin is enabled.

![Enable Plugin](ReadMeImages/2020-03-12_13-26-59.png)

## Connect Us

- You can find full API document at [Document Center](https://docs.agora.io/en/)

## Mac permissions

Add the following permissions in the info.plist file for device access:

Privacy - Camera Usage Description

Privacy - Microphone Usage Description

## iOS packaging
To package the project fot iOS, you need to generate **Signing Certificate** and **Provisioning Profile**. 
Follow the instructions from UE4 documentstion: [iOS Provisioning](https://docs.unrealengine.com/en-US/Platforms/Mobile/iOS/Provisioning/index.html)

Then you need to add the sertificate and provisioning profile to your project.

![iOS settings](ReadMeImages/iOSSettings.png)

Go to the **Edit->Project Settings->Platforms: iOS**, then select the sertificate and provisioning profile you created before. 

If you don't see one of them in the table, click  **Import Certificate** or **Import Provision**, chose the right file in Finder and click **Open**. 

Then enter a Bundle Identifier: it must be the Bundle Id you used while sertificate creation.

## iOS permissions
In the iOS you also need the following permissions:

Privacy - Camera Usage Description

Privacy - Microphone Usage Description

To add them in the info.plist go to the **Edit->Project Settings->Platforms: iOS** and enter the following line to Additional Plist Data: 
`<key>NSCameraUsageDescription</key><string>AgoraVideoCall</string> <key>NSMicrophoneUsageDescription</key><string>AgoraVideoCall</string>`

Now you are ready to package your project for iOS or launch it on iOS device.


