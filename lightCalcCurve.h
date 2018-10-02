// choose the Time, when the Arduino gets plugged in
int startTime = 15;

// adjust the array to your needs. {7, 0.05} meens 0.05% Power at 7:00
float times[24][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0.05}, {8, 0.1}, {9, 0.6}, {10, 1}, {11, 1}, {12, 1}, {13, 1}, {14, 1}, {15, 1}, {16, 1}, {17, 1}, {18, 1}, {19, 0.1}, {20, 0}, {21, 0}, {22, 0}, {23, 0}};

long oneHour = 3600000L;
void lightCalcCurveSetDev() {
  oneHour = 3600L;
}

float lightCalc(unsigned long milliseconds) {
  // as Key for the times array
  int startKey = (((unsigned long)milliseconds / (unsigned long)oneHour)) + (unsigned long)startTime;
  if (startKey > 23) {
    startKey = startKey - 24;
  }
  int endKey = startKey + 1;
  if (endKey == 24) {
    endKey = 0;
  }

  // The Lightness between the hours get a linear transition. So we need a Progress within the hours
  long elapsedMillisInHour = (long) milliseconds  % (long) oneHour;
  float progress = (float) elapsedMillisInHour / (long) oneHour;
  Serial.print(milliseconds);
  Serial.print(" startkey ");
  Serial.print(startKey);
  Serial.print(" prog ");
  Serial.print(progress);

  float before = times[startKey][1];
  float after = times[endKey][1];
  Serial.print(" before ");
  Serial.print(before);
  Serial.print(" after");
  Serial.print(after);

  float gain = (float) after - (float) before;
  Serial.print(" gain ");
  Serial.print(gain);

  float ret = (float) before + ((float) progress * (float) gain);
  Serial.print(" ret ");
  Serial.println(ret);
  return ret;
}
