# TrickyButtons

A plugin with a collection of button actors.

## Dependencies

This plugin required this plugins to work:

1. [**TrickyInteractionSystem**](https://github.com/TrickyFatCat/TrickyInteractionSystem) v2.0 and higher;
2. [**TrickyAnimationComponents**](https://github.com/TrickyFatCat/TrickyAnimationComponents) v2.0 and higher;

Install them before installing this plugin.

## Installation

The plugin can be used in both C++ and Blueprint projects.

### Blueprint projects

1. Download package file;
2. Install the plugin either in your project or for all projects in engine:
    * Unzip the package into Plugins folder of your project, e.g. `D:\UnrealProjects\MyProject\Plugins`;
    * Unzip the package to the Plugins folder in engine folder, e.g. `C:\Program Files\Epic Games\UE_5.0\Engine\Plugins`;
3. Restart the project;

In this case the plugin can be used for any blueprint project.

### C++ projects

1. Create the Plugins folder in the project directory;
2. Create the TrickyAnimationComponents folder in the Plugins folder;
3. Download the plugin source code into that folder;
4. Rebuild the project;

## Content

The plugin contains actors:

1. ButtonBase;
2. ButtonInteractive;
3. ButtonFloor;

### ButtonBase

A base button class with the most basic functionality.

#### Animation setup

The button uses the TimelineAnimationComponent from [**TrickyAnimationComponents**](https://github.com/TrickyFatCat/TrickyAnimationComponents).

You can find instructions how to adjust this component in the Git page.

#### Variables

1. `InitialStata` - the initial state of the button;
2. `IsReversible` - toggles if the button animation can be reversed;
3. `IsPressedTemporary` - if true, the button will stay in the pressed state for some time;
4. `PressedStateDuration` - how long button will state in pressed state;

#### Functions

1. `Press` - initiates button logic;
2. `SetIsEnabled` - toggles if the button enabled or disabled;

#### Delegates

1. `OnStateChanged` - called when the button changed its current state;
2. `OnReversed` - called when the button animation was reversed;

#### Implementable Events

1. `OnButtonStateChanged` - called when the button changed its current state;
2. `OnButtonReversed` - called when the button animation was reversed;
3. `OnButtondDisabled` - called when the button was disabled;
4. `OnButtonEnabled` - called when the button was enabled;

### ButtonInteractive

A button which requires interaction. Good for levers, switches, valves, etc.

It already has an interaction trigger and interface.

### ButtonFloor

A button which activated via a trigger. Good for buttons on floor.
