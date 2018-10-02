unsigned long epocheStart = millis();

unsigned long dayLength = 86400000UL; // Milliseconds in a day
void dailyEpocheSetDev() {
  dayLength = 86400UL; // 1000x faster for testing
}

unsigned long getDailyEpoche () {
  unsigned long elapsed = millis() - (unsigned long)epocheStart;  // elapsed: duration

  if (elapsed >= dayLength) {
    epocheStart = (unsigned long) epocheStart + (unsigned long) dayLength;
    Serial.println("new Day");
    return 0;
  } else {
    return ((unsigned long) elapsed);
  }
}
