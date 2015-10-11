# ELE410 Session5 : BLE

___
## Introduction
This project is the starting point for ELE410's session5 exercice.
We will now mix all that we've seen in the previous sessions. 

The objective is to implement a BLE device : "ELE410 prototype" which complies with the [provided specification](151012_ele410_session_5_ble_specification.pdf)
___
## Pre-requisites 

Having a proper development environment (cf. ELE410 Template Project)
___
## Template project description and suggestions
This project is a basis made from what had been presented in the previous sessions. 

An empty APP/ELE410Prototype module is already present and contains almost empty ele410_prototype.h and ele410_prototype.c files.

You should have a look at what was presented in session2, exercice3, how the solution was implemented, and inspire yourself to correctly implement this session's exercice. 

-> Most of the code you'll need write for this exercice should be in these 2 files (ele410_prototype.h and ele410_prototype.c).
-> you'll have to implement the BLE logic (services/characteristics declarations + management) in the BLE ()ble_common.c/ble_common.h or create your own files if needed; it could be more elegant). 

To control your development, you're invited to use tools such as :

- ANDROID (>4.3): [nRF Master Control Panel](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=en) from Nordic Semiconductor.
- iOS (>7.1 on >iPhone 4S / >iPad3 / >iPod 5th gen) : [LightBlue Explorer](https://itunes.apple.com/fr/app/lightblue-explorer-bluetooth/id557428110?mt=8) from Punch Through Design LLC. 

This kind of tools will allow you to interact with your BLE device, discover it, connect to it and play around with its GATT characteristics...

