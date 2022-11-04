# Part 5 I2C Traffic

In this part, we are asked to
- use the Lab 1 firefly code to generate ADPS9960 I2C traffic and display it on a lab oscilloscope
- take a screenshot of some portion of this exchange, and figure out/annotate what's happening based on the protocol documentation in the ADPS9960 datasheet

To start, I used the logic analyzer probe cable instead of regular probe to make it easier to anaylze the data. I used a 4 head cable to connect between APDS9960 and logic analyzer cable with the following instruction:

1. The red line, as the ground line of APDS sensor, connects to the ground line of logic analyzer cable.
2. The yellow line, as the clock line, connects to D0 of logic analyzer cable.
3. The blue line, as the data line, connects to the D1 of logic analyzer cable.
4. The red line, as the power line, stays unconnected.

Next, we set up the signal oscilloscope with the following steps:
- set the oscillscope to digital mode
- ignore data other than D0 to D7
- set the trigeer to falling edge
- press run/stop button to capture the data and clock data.
