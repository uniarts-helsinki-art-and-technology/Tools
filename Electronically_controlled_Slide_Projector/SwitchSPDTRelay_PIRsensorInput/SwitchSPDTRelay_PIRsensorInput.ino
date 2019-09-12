/*
  Switch

*/

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 0;    // the number of the pushbutton pin
const int ledPin = 12;

// Variables will change:
int switchState = LOW;         // the current state of the output pin
int buttonState;             // the current reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 10000;    // the debounce time; increase if the output flickers

int reading = 0;

boolean readyForNewReading = true;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  // read the state of the switch into a local variable:
  int analogReading = analogRead(A0);
  if (analogReading > 200) {
    reading = HIGH;
  }
  else {
    reading = LOW;
  }

  // If the switch changed, due to noise or pressing:
  if (reading == HIGH && readyForNewReading) {
    // reset the debouncing timer
    switchState = HIGH;
    digitalWrite(LED_BUILTIN, switchState);    // turn the LED off by making the voltage LOW
    digitalWrite(ledPin, switchState);   // turn the LED on (HIGH is the voltage level)
    lastDebounceTime = millis();
    readyForNewReading = false;
  }

  if ((millis() - lastDebounceTime) > debounceDelay && reading == LOW) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    switchState = LOW;
    digitalWrite(LED_BUILTIN, switchState);    // turn the LED off by making the voltage LOW
    digitalWrite(ledPin, switchState);   // turn the LED on (HIGH is the voltage level)
    readyForNewReading = true;
  }
  Serial.print("analogReading: ");
  Serial.print(analogReading);
  Serial.print(" switchState: ");
  Serial.println(switchState);
  delay(1);        // delay in between reads for stability

}
