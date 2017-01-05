# Feedback Strobe

Feedback strobe is a technology demonstration aid for EE422G Signals and Systems Laboratory at the University of Kentucky. Commisioned by [Dr. Kevin Donohue](https://www.engr.uky.edu/research/researchers/kevin-donohue/), the device will allow students to use LabView to monitor and control motor rotation speed, with the goal of tuning it such that strobing LEDs will 'stand still'

### Operation

<img src="images/feedback-strobe-data-flow.png">


### Physical Design
All structural parts in the Feedback Strobe were designed in Autodesk Inventor and printed on a 5th gen MakerBot Replicator (PLA filament). A slip ring is used to commutate both rotation speed and LED control signals. A LED-bar, the 'propellor' like part, was designed to hold the LEDs and IR reflectance sensor in place, to be driven by a motor with a pulley.

<img src="images/fbs-ir-close.jpg" width="600" />

An o-ring is used as the pulley. The 900 RPM micro-gear motor from Sparkfun was aligned such that its shaft would fit through one of the mounting holes of the slip ring. LED and IR sensor wires are routed through the center of the LED-bar, then through to the back side and attached.

<img src="images/fbs-exploded.jpg" width="600" />

The color-coded wires from the slip ring are then attached to the custom PCB, which hosts an LED buffer/driver, current limiting resistors for the LEDs, as well as a 5v regulator and motor control N-channel MOSFET. It also has a row of headers that line up with one side of the microcontroller, the Teensy-LC.

<img src="images/fbs-pcb-close.jpg" width="600" />

### Schematic and PCB

Data sheets for ICs used are in the ```docs/``` folder.

<img src="images/v2pcb-sch.png" width="800" />
<img src="images/v2pcb-brd.png" width="800" />

### In Action
Although the software is not quite finished, here is a picture of it while in motion.
<img src="images/fbs-action.jpg" width="600" />

Parts list:
- http://www.digikey.com/product-detail/en/on-semiconductor/MC78M05CDTRKG/MC78M05CDTRKGODKR-ND/1140087
- http://www.digikey.com/product-detail/en/vishay-siliconix/IRFL9110TRPBF/IRFL9110PBFCT-ND/812532
- http://www.digikey.com/product-detail/en/cui-inc/PJ-002AH-SMT-TR/CP-002AHPJCT-ND/669692
- http://www.digikey.com/product-detail/en/nichicon/UWT1C221MCL1GS/493-2179-1-ND/590154
- http://www.digikey.com/product-detail/en/triad-magnetics/WSU090-1300/237-1451-ND/3094977
- https://www.sparkfun.com/products/9453
- https://www.sparkfun.com/products/13305
- https://www.sparkfun.com/products/12316
- https://www.sparkfun.com/products/12248
- https://www.sparkfun.com/products/10635
- https://www.sparkfun.com/products/11121
- https://www.sparkfun.com/products/13065
- https://www.sparkfun.com/products/116
- https://www.sparkfun.com/products/553
