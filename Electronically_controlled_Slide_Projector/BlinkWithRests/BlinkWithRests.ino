/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.
*/

// note durations in millisecons:
int noteDurations[] = {
  4000, 500, 500, 500,
  333, 333, 333, 333
  333, 333, 333, 333,
  250, 250, 500, 500,
  1000, 1500, 2000, 3000
};

int noteNumber = 20;

int thisNote = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  int noteDuration = noteDurations[thisNote];
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(noteDuration * 0.5);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(noteDuration * 0.5);                       // wait for a second

  if (thisNote < noteNumber) {
    thisNote++;
  }
  else {
    thisNote = 0;
  }

}
