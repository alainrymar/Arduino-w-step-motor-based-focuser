# Arduino-w-step-motor-based-focuser

Wanna add a motor to drive your telescope focuser ? Probably yes and due to the fact that your equatorial mount is not as stable as you expected and just by touching the manual focuser, you get a very shaky image in your eye piece.
  
You can find here details about my project.

Based on Arduino UNO, a motor driver a4988 and a step motor.
I added also a 3D STL file to attach the motor to a real telescope. This one is for a SkyWatcher Startravel 102, but it’s up to you to developp your own motor support for your telescope. https://cults3d.com/en/3d-model/various/telescope-motorized-focuser


Motorised Focuser : Components list
-	1 x Arduino Uno
-	1 x Stepper Motor drive a4988
-	1 x 7mmx7mm 6 Pin 42 SMD SMT Tactile Switch (Joystick like)
-	4 x 4 pin Tactile Push Button switch DIP for Arduino DIP
-	1 x OLED Screen 0.91 » 128x32 IIC SSD1306 (Not displayed on the Schematic. Just connect it in a legacy way (VCC/GND/SDA/SCL) to the I2c pins on Arduino Uno).
-	7 x 10nf capacitors
-	7 x 10kOhms resistors
-	1 x Prototype PCB for Arduino UNO R3 Shield Board DIY
-	1 x KF2510-4 2.54mm Pin Header+Terminal+Housing Connector Kit
-	1 x  Step Motor 42SHDC3025-24B
- 1 x Step motor coupler (link the step motor to the focuser axis)


Check-out the Arduino Code for details.
How it works ?

Handle 4 Focuser speeds (Fast, Medium, Slow, Very Slow) = steps per 360° (400, 800, 1600, 3200)
At boot, motor is not engaged, manual focus is possible,
Joystick clic to engage motor (manual focus not possible),
Use one of the buttons to change focus speed,
Joystick up or down to focus,
Joystick clic to disable motor (Manual focus available).
