`# Feedback Strobe

Feedback strobe is a technology demonstration aid for EE422G Signals and Systems Laboratory at the University of Kentucky. Commisioned by [Dr. Kevin Donohue](https://www.engr.uky.edu/research/researchers/kevin-donohue/), the device will allow students to use LabView to monitor and control motor rotation speed, with the goal of tuning it such that strobing LEDs will 'stand still'

### Operation

<img src="images/feedback-strobe-data-flow.png">


### Physical Design
All structural parts in the Feedback Strobe were designed in Autodesk Inventor and printed on a 5th gen MakerBot Replicator (PLA filament). A slip ring is used to commutate both rotation speed and LED control signals. A LED-bar, the 'propellor' like part, was designed to hold the LEDs and IR reflectance sensor in place, to be driven by a motor with a pulley.

All CAD models can be viewed on GitHub by accessing the ```.stl``` files in the ```cad/stl/``` [directory](https://github.com/ruffner/feedback-strobe/tree/master/cad/stl).

<img src="images/fbs-ir-close.jpg" width="800" />

An o-ring is used as the pulley. The 900 RPM micro-gear motor from Sparkfun was aligned such that its shaft would fit through one of the mounting holes of the slip ring. LED and IR sensor wires are routed through the center of the LED-bar, then through to the back side and attached.

<img src="images/fbs-exploded.jpg" width="800" />

The color-coded wires from the slip ring are then attached to the custom PCB, which hosts an LED buffer/driver, current limiting resistors for the LEDs, as well as a 5v regulator and motor control N-channel MOSFET. It also has a row of headers that line up with one side of the microcontroller, the Teensy-LC.

<img src="images/fbs-pcb-close.jpg" width="800" />

### Schematic and PCB

Data sheets for ICs used are in the ```docs/``` folder.

<img src="images/v2pcb-sch.png" width="800" />
<img src="images/v2pcb-brd.png" width="800" />

Finished v2.1 PCB:

<img src="images/v2pcb-top.jpg" width="500" />
<img src="images/v2pcb-bottom.jpg" width="500" />


### In Action
Although the software is not quite finished, here is a picture of it while in motion.
<img src="images/fbs-action.jpg" width="800" />

The following scope traces are of the IR reflectance sensor output while rotating at full speed. The 'valleys' in the signal occur when the IR reflectance sensor in the LED-bar pass over the drive pulley attached to the motor. The tip of the drive pulley could be covered in a more reflective material (e.g. white paper or whiteout) to dramaticize the change in signal. 

This shows the interval between valleys, representing the rotation period.
<img src="images/scope-speed.png" width="800" />

This shows the voltage difference between the valley minimum and average when not in a valley.
<img src="images/scope-mag.png" width="800" />

### Parts
In the ```docs``` folder, [here](docs/Feedback Strobe Parts List.pdf)
