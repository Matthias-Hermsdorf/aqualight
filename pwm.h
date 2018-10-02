/* von  https://arduino-projekte.webnode.at/registerprogrammierung/fast-pwm/ */
// We use a 10 Bit PWM Signal. So we need to use
// Pin D9

void pwmSetup () {
  //Delete Timer/Counter Control Register A and B
  TCCR1A = 0;
  TCCR1B = 0;

  //Set Fast PWM-Mode 10 Bit Mode
  TCCR1A |= (1 << WGM10) | (1 << WGM11);
  TCCR1B |= (1 << WGM12);

  //Set Prescaler to 8
  TCCR1B |= (1 << CS11);

  //Set the notinverted PWM-Signal
  TCCR1A |= (1 << COM1A1);

  // Define PWM-Pin 9
  DDRB |= (1 << DDB1);
}

void pwmSet (int value) {
  // the value has to be between 0 and 1023
  if (value == 255) {
    value = 254;
  }
  analogWrite(9, value);
}
