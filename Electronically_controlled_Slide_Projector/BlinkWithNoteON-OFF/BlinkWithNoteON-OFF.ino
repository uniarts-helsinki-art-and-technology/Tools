/*
  
  
  
  
  */

// note durations in millisecons in pairs of note on and note off:
int noteDurations[] = {
  4000, 1000, 100, 2000,
  100, 2000, 100, 2000
};

int noteNumber = 8;

int thisNote = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  int noteDuration1 = noteDurations[thisNote];
  int noteDuration2 = noteDurations[thisNote + 1];
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(noteDuration1);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(noteDuration2);                       // wait for a second

  if (thisNote < noteNumber - 1) {
    thisNote = thisNote + 2;
  }
  else {
    thisNote = 0;
  }

}
