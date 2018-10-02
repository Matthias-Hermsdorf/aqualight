Aqualight
=========

A Arduino Sketch for a aquarium light with day-night-cycle and a smooth 10bit twighlight.
-----------------------------------------------------------------------------------------

I got a 60l aquarium with an small gloomy light. To

I glued a 1,8m 12V LED Stripe with 1800lm and a RA 90 Colorindex in the Header.
It draws about 15W. These  30lm/l brightens the aquarium in a nice light. At day
it is enough to let the plants grow. And at morning and evening its dimmed to a
vastly lower value, which makes the aquarium to a pleasant ambient Light.

You need

-   12V Led Stripe

    -   12V power adapter

    -   Arduino (Nano)

    -   Mosfet (to switch the high currents)

    -   perhaps a voltage regulator

    -   wires, soldering iron, tools...

    -   No real time clock is required

 

Light Calculation
-----------------

The light calculation uses a array with a length of 24 items. You can set a
lightlevel for every full hour. A linear transition is made between the levels.

see lightCalcCurve.h

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float times[24][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0.05}, {8, 0.1}, {9, 0.6}, {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, {18, 1}, {19, 0.1}, {20, 0}, {21, 0}, {22, 0}, {23, 0}};
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In earlier versions I used a sinus transition. But that made the lightlevel less
predictable. And the because of the long transition you will not notice the
difference.

There is not real time clock. So the Arduino does not know the current time. But
it knows the time since startup.  
Set startTime to your next full hour and reset the Arduino when the time has
come.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int startTime = 13;
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

DevMode
-------

In aqualight2.ino you can set

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
devMode = true; 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Then the cycle gets accelerated to 1000x.

SerialMode
----------

If you send a number over serial to the Arduino, the lightcylce gets stopped and
the number sets the new brightness. This is useful to calibrate the brightness
in the twilight hours.

Buttons?
--------

No, there are no buttons except the arduino reset button yet. If you need a more
detailed user interface, perhaps you should use a esp8266 or similar.

How do you get the 10bit pwm?
-----------------------------

The pwm script comes from
[arduino-projekte.webnode.at](https://arduino-projekte.webnode.at/registerprogrammierung/fast-pwm/)
. The common analogWrite function uses 8bit to use all three timers for pwm. But
one of these timers is capable to output a 10bit signal on Pin D9 and D10.

Different Colors
----------------

In an earlier Version a used a Neopixel RGB Strip. It works with 5V, you need no
mosfet and it has a arduino library. Sounds fine. But it emits 3 peaks of light.
This is nice for special effects for your fish, but it looks strange. And the
leds are not as efficient as 12V LED stripes are.

Possibly you an choose the really expensive LED stripes where you can choose the
light temperature. Inside there are warm white and cold white LEDs in 2
substripes. For those Stripes you could extend the sketch to use 2 light level
arrays to output 2 PWM Signals.

Why the voltage regulator
-------------------------

The first 2 weeks everything went fine without it. But then strange Things
happen. The millis() returned the same value every time, when powered on 12V.
But if I attached the laptop via USB, everything was fine.

So I changed the Arduino. The second made find timings. But on every dimming pwm
the light flickered and the Arduino stopped working.

My 12V power supply supplied 14.8V. And this is obviously a bit to much for my
Arduino Nano clone.

Now i have a step down module in between, which should output a 5V voltage. The
measurement revealed 6.2V, but that's ok for the Arduino.
