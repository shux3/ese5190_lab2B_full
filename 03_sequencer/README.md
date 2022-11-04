# Part 3 Sequencer (in progress)

In this part, we are asked to create a 'sequencer' that can record BOOT button presses and play them on the Neopixel, and also play a sequence of read/write commands. This 'sequencer' should be able to:

- record at a least a few seconds of button input to your RP2040 (in RAM)
- replay a recorded sequence on your NeoPixel
- loop a recording
- save a recording to your laptop (the Python Serial library is one way to do this)
- play a recording from your laptop
- record 'macros' (a sequence of console commands) based on keystrokes in your serial console
- hand-edit a list of register read/write commands on your laptop, and play them on the RP2040
- include multiple I/O sources in a recording, and remap among the following:
    - inputs: BOOT button, console commands, register read/write commands
    - outputs: neopixel color, neopixel brightness, data over serial, register read/write commands
    
## My plan:
    
To acheive the goals listed above, I plan to build a C program based on part 2 to implement User I/O through serial console which contains the command to

1. record the input to RP2040
2. play
3. loop play
4. record 'macros' through console
5. read register read/write commands that is hand-edit by users, possibly a *txt* or a *csv* file

To record the button inputs/ regiser command, I plan to start a python file that read/write to a csv file to store the sequences whenever being called. 
