// v4
// Aqualight
// A Arduino Sketch for a aquarium light with day-night-cycle and a smooth 10bit twilight.

// For PWM use Pin D9

// The Brightness in every hour and the Starttime is configurable in the lightCalcCurve.h. 

// The devMode shortens the Day to 1/1000.
const bool devMode = false;

// If you send a number over the serial connection to the Arduino, the DayNightProgram stops and the Number sets the 
// new Lightlevel. This is usefull to calibrate the brightness in the twilights.
bool serialMode = false;

#include "lightCalcCurve.h"
#include "dailyEpoche.h"
#include "pwm.h"

int minLight = 0;
int maxLight = 1023;


void setup() {
  pwmSetup();
  Serial.begin(57600);
  if (devMode) {
    dailyEpocheSetDev();
    lightCalcCurveSetDev();
  }

  // Optical Feedback, everything is ready
  setLightness(0);
  delay(250);
  setLightness(50);
  delay(250);
  setLightness(0);
  delay(250);
}

void loop() {
  if (!serialMode) {
    unsigned long epoche = getDailyEpoche();
    float lightScalar = lightCalc(epoche);

    float lightLevel = (minLight + lightScalar * (maxLight - minLight));
    setLightness(lightLevel);
  }

  if (devMode || serialMode) {
    delay(50);
  } else {
    delay(5000);
  }
}

float setLightness(int w) {
  w = max(0, min(w, maxLight));
  pwmSet(w);
}

void serialEvent() {
  serialMode = true;
  int lightLevel = Serial.parseInt();
  Serial.flush();
  pwmSet(lightLevel);
}
