// note durations in millisecons in pairs of note on and note off:
int noteDurations[] = {
  4000, 1000, 200, 4000,
  200, 4000, 200, 4000
};

int noteNumber = 8;

int thisNote = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // open the serial port at 9600 bps:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  if (thisNote > noteNumber - 2) {
    thisNote = 0;
  }

  int noteDuration1 = noteDurations[thisNote];
  int noteDuration2 = noteDurations[thisNote + 1];
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.print("thisNote: ");
  Serial.print(thisNote);
  Serial.print(" noteDuration1 ");
  Serial.println(noteDuration1);
  delay(noteDuration1);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  Serial.println(noteDuration2);
  delay(noteDuration2);                       // wait for a second
  thisNote = thisNote + 2;

}
