# Part 5 I2C Traffic

In this part, we are asked to Create a REPL to let you read and write RP2040 registers from a console. We should be able to:

- select any 32-bit address to read/write (even if not a valid RP2040 address)
- read/write any 32-bit value to this address
- read/write using any of the atomic bit-setting aliases and a 32-bit mask

This part of code is based on code from part 1. I have updated the status with parameters that can store 
- last serial byte value
- bootsel button pressed status
- a flag to note read/write status
- register address
- register value


Notice that this part of code gives you access to read/write to any 32-bit address that is not restricted by RP2040 availability. However, the program might freeze when acessing invalid addresses.
