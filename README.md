# Ivi Demo for ApiGear

## IviLab

The IviLab is a simple Unreal Engine project that will be used as a starting point for the ivi integration.

It contains a MainMap with an attached UIManager Blueprint Actor. The UIManager will be used to display the Main Menu.
The Main Menu will contain a button to scan for tuner stations.

Tasks:
* Run apigear to generate the plugin code.
    `apigear generate solution apigear/ivilab.solution.yaml`
* Build the project and open the Unreal Editor.


### Main Menu Widget

* Create a new UserWidget called MainMenu.
* Inside MainMenu use a Canvas and center a Button (called ScanStationsButton) with a Text "Scan Stations" as child.
* Make sure ScanStationsButton is exposed as a variable.

### UIManager Blueprint Actor

* Create a new Blueprint Actor (UIManager)
* Inside use the Create Widget node to create the Main Menu during BeginPlay. Make sure the widget is added to the viewport.

### Main Map

* Create a new Simple Level called MainMap and save it
* Add the UIManager Blueprint Actor to the level.
* Now when the game starts the Main Menu should be displayed.

## C++ Plugin Integration

### Generate Plugin
* Go to the console and run `apigear generate solution ivi.tuner.solution.yaml`,
* Several plugins inside the Unreal Engine Project will appear.
* Build the project and open the Unreal Engine Editor.


### Insert C++ Implementation

* Inside the C++ file `Plugins/IviTuner/Source/IviTuner/Private/Implementation/IviTunerTuner.cpp`
* Add a log statements to the ScanStations function.

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

* Inside you MainMenu Blueprint Actor, add a handler to the OnClicked event of the ScanStationsButton.
* Place the `Get Ivi Tuner Tuner` node and drag out the `ScanStations` function and connect it to the OnClicked event.


### Run the UI

* Now run the UI and click the Scan Stations button. You should see the log statement in the output log.
* Integration is complete. :-)

## Final Working UI

* Show the final working UI with the Scan Stations button and the log statement in the output log.
```


# Project Layouts

## Ivi Laboratory

The IviLab will have the bare bone code and a guideline how to integrate the ivi backend into the Unreal Engine.

## Ivi Solution

The IviSolution will have the integration of the ivi backend into the Unreal Engine.

## Ivi Demonstration

The IviDemonstration will have the full integration of the ivi backend into the Unreal Engine and a demonstration of the UI.
