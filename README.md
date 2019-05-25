# Scorpions et gerbilles : dynamique des populations et modèle neuronal de la prédation 
This project was developped during the introductory object oriented programming course (CS-112(i)) at EPFL.
It provide a simulation of scorpions and gerbils in a toric world.

This project was tested :

     - On Linux Mint 18.2 Cinnamon 64-bit
     - On Ubuntu VM on CO thinclient at epfl.

## Prerequisites

    - scons
    - [SFML](https://www.sfml-dev.org/documentation/2.3/)

## Installation
Unzip the project archive where you want to install the simulation program. The directory base directory will be referenced as baseDir for the following steps:

### Build

```
    cd baseDir/partie6
    scons application --cfg=app.json
```

### Run
```
    cd baseDir/partie6/build
    ./application
```

### Build and run

```
    cd baseDir/partie6
    scons application-run --cfg=app.json
```

## Usage
The program offer two simulation, to switch between the simulations, use the TAB key.

The following commands are availables during the Predator Prey Simulation :
        
     R     : Reset the simulation
     Esc   : End of program
     C     : Reload config file
     G     : Add a gerbil at MP
     S     : Add a scorpion at MP
     F     : Add a food at MP
     D     : Toggle debug mode
     Tab   : Switch macro/micro view
     Z     : Zoom
     ->    : Move view to right
     <-    : Move view to left
     Space : Pause

The following commands are availables during the Neuronal Simulation :

     R     : Reset the simulation
     Esc   : End of program
     C     : Reload config file
     N     : Add a neuronal scorpion at MP
     W     : Add a wave gerbil at MP
     D     : Toggle debug mode
     Tab   : Switch macro/micro view
     Z     : Zoom
     ->    : Move view to right
     <-    : Move view to left
     Space : Pause

## Config files
The configuration files of the simulations are located in baseDir/partie6/res. The default JSON file to use is app.json. The others are related to previous state of the project. The user can edit the values in app.json in order to change the parameters of the simulation. If an other JSON file is used, it just has to passed to the cfg parameters, i.e.:

    - scons application-run --cfg=YOUR_CUSTOM_FILE.json 

