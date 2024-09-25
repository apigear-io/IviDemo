# Ivi Demo for ApiGear

This repository contains Unreal Engine projects that demonstrate how to integrate the ivi backend into the Unreal Engine using ApiGear.

- `IviLab`, An almost completely empty project that will be used as a starting point for the ivi integration with a single button to scan for tuner stations.
- `IviSol` A project that contains the ivi backend and a demonstration of the UMG UI for the lab.
- `IviDemo` A more complete project that contains a fully functional ivi backend and a demonstration of the UMG UI. 

## IviLab

The IviLab is a simple Unreal Engine project that will be used as a starting point for the ivi integration.

It contains a `MainMap` with an attached `UIManager` Blueprint Actor. The `UIManager` will be used to display the main menu.
The main menu will contain a button to scan for tuner stations.

Tasks:
* Run apigear (apigear.io)to generate the plugin code.
    `apigear generate solution apigear/ivilab.solution.yaml`
* Build the project and open the Unreal Editor.


### Main Menu Widget

* Create a new `UserWidget` called `MainMenu`.
* Inside `MainMenu` use a `Canvas` and center a `Button` (called `ScanStationsButton`) with a Text "Scan Stations" as child.
* Make sure `ScanStationsButton` is exposed as a variable.

### UIManager Blueprint Actor

* Create a new Blueprint Actor called `UIManager`
* Inside use the `Create Widget` node to create the Main Menu during `BeginPlay`. Make sure the widget is added to the viewport.

### Main Map

* Create a new Simple Level called `MainMap` and save it
* Add the `UIManager` Blueprint Actor to the level.
* Now when the game starts the Main Menu should be displayed.

## C++ Plugin Integration

### Generate Plugin
* Go to the console and run `apigear generate solution ivi.tuner.solution.yaml`,
* Several plugins inside the Unreal Engine Project will appear.
* Build the project and open the Unreal Engine Editor.


### Insert C++ Implementation

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

### Attach C++ Scan Stations call to Main Menu UI

* Inside you `MainMenu` Blueprint Actor, add a handler to the `OnClicked` event of the `ScanStationsButton`.
* Place the `Get Ivi Tuner Tuner` node and drag out the `ScanStations` function and connect it to the `OnClicked` event.


### Run the UI

* Now run the UI and click the "Scan Stations" button. You should see the log statement in the output log.
* Integration is complete. :-)

## IviSol

IviSol is a project that contains the ivi backend and a demonstration of the UMG UI for the lab.

Use it to lookup the ivi backend code and the UMG UI code for the IviLab.

## IviDemo

IviDemo is a more complete project that contains a fully functional ivi backend and a demonstration of the UMG UI.

It provides a more complete UMG UI with several tabs and a fully mocked ivi backend. 
Use this to see how larger projects can be integrated with the ivi backend and for patterns of UMG UI development.
