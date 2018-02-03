# Audio Router

@audiorouterdev created a similar app that does exactly what CheVolume does, except this is free.

[Downloads](https://github.com/a-sync/audio-router/releases/)

[Here's a simple gif to show how it's used.](http://i.imgur.com/uq6ApMe.gif)

Changelog 0.10.5:

* New feature: option to start minimized to tray (`/min`)
* Bugfix when populating the device list

Changelog 0.10.4:

* Exit on close button
* Added Exit menu option to File menu
* Removed telemetry
* Build updates

Changelog 0.10.3:

* Automatic routing enabled
* Minimize to tray

Changelog 0.10.2:

* Automatic routing functionality disabled because it caused some problems with certain software.
* Removed testing license from the executable.
* Source code released!

Changelog 0.10.1:

* The bug that blocked some programs from starting in Windows 10 is now fixed.

Changelog 0.10:

* New feature: saved routings. Now you can save the routing for an application so when the app starts next time it will be automatically routed(Audio Router must be opened so the app can be automatically routed). The feature will also allow routing applications that can't be routed otherwise. The UI for saving the routing is not very user-friendly at the moment, but it will be improved. Unfortunately apps that need administrator rights can't be automatically routed. This is a new feature, so I'd appreciate reporting all the bugs you come across.
* Initial licensing implementation.
* Very minor changes and bug fixes.

Changelog 0.8.5:

* Audio Router now requires administrator rights to start.
* A bug that caused the output device not to initialize correctly when routing or duplicating should be now fixed.
* Few very minor changes.

Changelog 0.8:

* Peak meters added to processes that output audio.
* A bug that caused Audio Router to crash when selecting the output device is now fixed.

Changelog 0.7.3.2:

* A bug that caused Audio Router not to start when using Voicemeeter Banana is now fixed.

Changelog 0.7.3.1:

* A bug that caused Audio Router not to start for some people should be now fixed.

Changelog 0.7.3:

* Recording device audio cut off after routing should be now fixed(routing to a new device earlier would mute the microphone).
* A bug related to duplication which might have crashed the target process or made the duplicated audio stream buggy is now fixed.
* The routing method changed a bit. If the target process won't route anymore(or duplicate), send me a PM.

Changelog 0.7.1:

* Icons added.
* More descriptive names for process names.

Changelog 0.7:

* New feature: audio duplication. Now you can duplicate the audio stream so it plays on many separate audio devices. This is a new feature, so it probably has some bugs in it. Also, it seems that the duplication doesn't work if the devices have different audio configurations(e.g stereo and 5.1 configurations).

Changelog 0.6:

* Greatly improved routing. Now programs like Hearthstone(and probably Spintires) will route aswell.
* "Soft routing" option added to the route selection dialog. "Soft route" is the old method of routing, which fails more often. It's still included as soft routing, because it won't cut out the currently playing audio streams, unlike the new routing.
* Metro apps are now possible to route. Unfortunately they still won't route straight out of the box, but if you need route metro apps too, send me a PM and I'll give instructions on how to enable the feature.

Current known bugs:

* Scroll bars slightly cover other UI elements.
* The UI elements are repositioned wrongly sometimes when an update occurs.
* Routing audio to a new device does not delete old audio sessions, so the windows volume mixer fills up with unused sessions.

Minimum supported OS version: Windows 7
