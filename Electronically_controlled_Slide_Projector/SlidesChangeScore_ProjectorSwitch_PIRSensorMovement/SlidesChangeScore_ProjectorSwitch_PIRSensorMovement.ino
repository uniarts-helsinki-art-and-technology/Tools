

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(int)))

// SETUP
// Set the following times!

// note durations in milliseconds in pairs of note on and note off:
// first time is for changing the slide (approx 200 ms. should be fine for KODAK CAROUSEL 2050)
// second time defines how long the slide will be displayed

int noteDurations[] = {
  200, 1000,  // slide1
  200, 2000,  // slide2
  200, 2000,  // slide3
  200, 2000   // etc
};

const int numerOfLoopsBeforeSwitchOff = 3;

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// YOU DON'T NEED TO CHANGE THE FOLLOWING LINES

int noteNumber;     // total number of notes
int thisNote = 0;   // current slide number
int startNote = 0;  // start the array from 0

// constants won't change. They're used here to set pin numbers:
const int pirSensorPin = 0;    // the number of the pushbutton pin
const int switchPowerProjector = 12;
const int relayPin = 8;

// Variables will change:

// NOTE!!! the logic is inverted so LOW means projector On and viceversa

int switchProjectorState = LOW;         // the current state of the output pin

int reading = 0;

int currentLoop = 1;


// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(9600);              // open the serial port at 9600 bps:
  pinMode(LED_BUILTIN, OUTPUT);    // initialize digital pin LED_BUILTIN as an output.
  pinMode(switchPowerProjector, OUTPUT);    // initialize digital pin LED_BUILTIN as an output.
  pinMode(relayPin, OUTPUT);    // initialize digital pin LED_BUILTIN as an output.
  digitalWrite(switchPowerProjector, switchProjectorState);   // switch on the projector

  int sizeOfMyArray = sizeof(noteDurations) / sizeof(int);
  noteNumber =  sizeOfMyArray; // set the total number of notes according to the array
  Serial.print(noteNumber);

  // give some time to the projector to be up & running
  delay(5000);
}

// the loop function runs over and over again forever
void loop() {

  if (currentLoop <= numerOfLoopsBeforeSwitchOff) {

    if (thisNote > noteNumber - 2) {                // LOOP (if the all values are read, start from 0)
      thisNote = startNote;
      currentLoop++;
    }

    int noteDuration1 = noteDurations[thisNote];      // read data value from array
    int noteDuration2 = noteDurations[thisNote + 1];  // read another data value from array

    digitalWrite(LED_BUILTIN, HIGH);                  // turn ON (HIGH is the voltage level)
    digitalWrite(relayPin, HIGH);
    delay(noteDuration1);                       // time for change time

    digitalWrite(LED_BUILTIN, LOW);             // turn OFF (by making the voltage LOW)
    digitalWrite(relayPin, LOW);
    delay(noteDuration2);                       // Show slide for specified time

    thisNote = thisNote + 2;

    if (currentLoop == numerOfLoopsBeforeSwitchOff) {
      int analogReading = analogRead(A0);
      if (analogReading > 200) {
        currentLoop--;
      }
    }
  }
  else {
    if (switchProjectorState == LOW) {
      switchProjectorState = HIGH;
      digitalWrite(switchPowerProjector, switchProjectorState);   // switch off the projector
    }
    int analogReading = analogRead(A0);
    if (analogReading > 200) {
      switchProjectorState = LOW;
      digitalWrite(switchPowerProjector, switchProjectorState);   // switch on the projector
      // wait some seconds before starting the sequence
      delay (5000);
      currentLoop = 1;
    }
  }

  Serial.print("currentLoop ");
  Serial.print(currentLoop);
  Serial.print(": thisNote ");
  Serial.println(thisNote);
}
