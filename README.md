# Simple Ivi Demo for [ApiGear](https://apigear.io)

This repository contains Unreal Engine projects that demonstrate the integration of an ivi backend into the [Unreal Engine](https://www.unrealengine.com) using [ApiGear](https://apigear.io).

![IviDemo Screenshot](ivituner.png)

*Note: If you want to see the finished demo, you can just run the `IviDemo` project.*

Folder/Projects

- `apigear` Contains the ivi.tuner.idl file that describes the ivi backend.
- `IviLab`, An almost completely empty project that will be used as a starting point for the ivi integration with a single button to scan for tuner stations.
- `IviSol` A project that contains the ivi backend and a demonstration of the UMG UI for the lab.
- `IviDemo` A more complete project that contains a fully functional ivi backend and a demonstration of the UMG UI. 

## Prerequisites

- Unreal Engine 5.4 or newer
- ApiGear v0.40.0 or newer
- A C++ IDE (e.g. Visual Studio Code, or Visual Studio 2022, of JetBrains Rider)

Optional:

- Taskfile (https://taskfile.dev) to run the build and test tasks

## apigear

The apigear folder contains the `ivi.tuner.idl` file that describes the ivi API surface. It is used by the ivi projects to generate the ivi backend code.
The `*.solution.yaml` files are used by apigear to configure the ivi backend code generation. They are used with the apigear tool (see htps://apigear.io).

In general you can use the `apigear generate solution <solution.yaml>` command to generate the ivi backend code. This would generate UE Plugin code into the defined output folder.

Most generated files will be overwritten when you run the command again. But some files which are meant to be changed by the developer are not overwritten (e.g. all files inside the `Implementation` folder).

## IviLab - A simple lab project for the ivi integration

The IviLab is a simple Unreal Engine project that will be used as a starting point for the ivi integration.

We will create a simple level called `MainMap` and add a Blueprint Actor called `UIManager` to it. 
The `UIManager` will be used to display the main menu.
At the end the main menu will contain a button to scan for tuner stations, which makes a call to the C++ implementation of the ivi backend.

### Steps

#### Blueprint Creation

* Run apigear (see https://apigear.io) to generate the plugin code.
   * `apigear generate solution apigear/ivilab.solution.yaml`
   * Build the project and open the Unreal Editor.

* Create `MainMenu` User Widget
   * Create a new `UserWidget` called `MainMenu`.
   * Inside `MainMenu` use a `Canvas` and center a `Button` (called `ScanStationsButton`) with a Text "Scan Stations" as child.
   * Make sure `ScanStationsButton` is exposed as a variable.

* Create `UIManager` Blueprint Actor
	* Create a new Blueprint Actor called `UIManager`
	* Inside use the `Create Widget` node to create the Main Menu during `BeginPlay`. Make sure the widget is added to the viewport.

* Create `MainMap` level
   * Create a new Simple Level called `MainMap` and save it
   * Add the `UIManager` Blueprint Actor to the level.
   * Now when the game starts the Main Menu should be displayed.

#### C++ Plugin Integration

* Generate Plugin
    * Go to the console and run `apigear generate solution ivi.tuner.solution.yaml`,
    * Several plugins inside the Unreal Engine Project will appear.
    * Build the project and open the Unreal Engine Editor.


* Insert C++ Implementation

   * Open your C++ IDE and open the file `Plugins/IviTuner/Source/IviTuner/Private/Implementation/IviTunerTuner.cpp`
   * Inside the C++ file add a log statements to the `ScanStations` function.

		```cpp
		void UIviTunerTuner::ScanStations_Implementation(EIviTunerWaveband Waveband)
		{
			(void)Waveband;
			UE_LOG(LogIviTuner, Warning, TEXT("Scan Stations"));
			// do business logic here
		}
		```
   * Build the project and open the Unreal Engine Editor.

* Attach C++ Scan Stations call to Main Menu UI

   * Inside you `MainMenu` Blueprint Actor, add a handler to the `OnClicked` event of the `ScanStationsButton`.
   * Place the `Get Ivi Tuner Tuner` node and drag out the `ScanStations` function and connect it to the `OnClicked` event.


* Run the UI
  * Now run the UI and click the "Scan Stations" button. You should see the log statement in the output log.
  * Integration is complete. :-)

## IviSol - The solution to the lab

IviSol is a project that contains the ivi backend and a demonstration of the UMG UI for the lab.

Use it to lookup the ivi backend code and the UMG UI code for the IviLab.

## IviDemo - A more complete project for the ivi integration

IviDemo is a more complete project that contains a fully functional ivi backend and a demonstration of the UMG UI.

It provides a more complete UMG UI with several tabs and a fully mocked ivi backend. 
Use this to see how larger projects can be integrated with the ivi backend and for patterns of UMG UI development.

## License

This project is licensed under the MIT License.