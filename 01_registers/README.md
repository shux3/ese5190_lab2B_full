# Part 1 Registers

In this part, we are asked to toggle the Qt Py's Neopixel LED when the BOOT button is pressed, using only direct register reads to access the boot button status. It is okay to use the SDK to initialize the board and the pins, and the WS2812 example code to toggle the Neopixel.

The code in this part is based on given example *flashlight* with changes that directly read/write to registers instead of calling built-in functions. Notice that the specific register values and registers and be found by *go to the reference* of built-in initialzation functions and *set/get functions*.
