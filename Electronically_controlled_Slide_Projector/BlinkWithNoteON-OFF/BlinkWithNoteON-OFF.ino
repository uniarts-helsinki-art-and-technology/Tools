
// SETUP
// Set the following times!

// note durations in milliseconds in pairs of note on and note off:
// every second time is for changing the slide (approx 200 ms. should be fine)

int noteDurations[] = {
  200, 1000, // slide1
  200, 4000,  // slide2
  200, 4000,  // slide3
  200, 4000
};


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// YOU DON'T NEED TO CHANGE THE FOLLOWING LINES

int noteNumber;     // total number of notes
int thisNote = 0;   // current slide number
int startNote = 0;  // start the array from 0


// the setup function runs once when you press reset or power the board
void setup() {
  // open the serial port at 9600 bps:
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  noteNumber =  sizeof(noteDurations); // set the total number of notes according to the array
}

// the loop function runs over and over again forever
void loop() {

  if (thisNote > noteNumber - 2) {                // LOOP (if the all values are read, start from 0)
    thisNote = startNote;
  }

  int noteDuration1 = noteDurations[thisNote];      // read data value from array
  int noteDuration2 = noteDurations[thisNote + 1];  // read another data value from array
  
  digitalWrite(LED_BUILTIN, HIGH);                  // turn ON (HIGH is the voltage level)
  
  Serial.print("thisNote: ");
  Serial.print(thisNote);
  Serial.print(" noteDuration1 ");
  Serial.println(noteDuration1);
  
  delay(noteDuration1);                       // time for change time
  
  digitalWrite(LED_BUILTIN, LOW);             // turn OFF (by making the voltage LOW)
  
  Serial.println(noteDuration2);
  
  delay(noteDuration2);                       // Show slide for specified time
  thisNote = thisNote + 2;

}
