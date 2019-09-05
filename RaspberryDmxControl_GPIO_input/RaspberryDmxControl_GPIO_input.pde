import processing.io.*;
import dmxP512.*;
import processing.serial.*;

float aloitusAika = 92; // aika sekunteina 92
float kesto = 26; // kuinka pitkään tuulikone on päällä? kesto sekunteina 
int tuulikoneVoimakkuus = 120; // between 0 - 255, minimi teho 0, maksimi teho 255

float timeStamp = 0;
float startTimeStamp = 0;// for debugging 
boolean isOn =false;
boolean isWaiting = true;

DmxP512 dmxOutput;
int universeSize=128;

boolean LANBOX=false;
String LANBOX_IP="192.168.1.77";

boolean DMXPRO=true;
String DMXPRO_PORT="/dev/ttyUSB0";//case matters ! on windows port must be upper cased.
int DMXPRO_BAUDRATE=115000;


void setup() {
  size(40, 40, JAVA2D);  
  background(255, 255, 255);

  GPIO.pinMode(4, GPIO.INPUT);
  dmxOutput=new DmxP512(this, universeSize, false);

  if (LANBOX) {
    dmxOutput.setupLanbox(LANBOX_IP);
  }

  if (DMXPRO) {
    dmxOutput.setupDmxPro(DMXPRO_PORT, DMXPRO_BAUDRATE);
  }
  dmxOutput.set(1, 0);
}


void draw() {    

    if (GPIO.digitalRead(4) == GPIO.HIGH && !isOn && isWaiting) { 
      timeStamp=millis();
      println("Pin triggered at: "+timeStamp);
      isWaiting=false;
    }
    
      float timeDelta = millis() - timeStamp;
 // println(timeDelta);

    if (timeDelta >= aloitusAika*1000.0 && timeDelta < (aloitusAika+kesto)*1000.0 && !isOn) {
      isOn = true;
      control();
      background(0, 255, 0);
      startTimeStamp=millis();
      println("Power on! Start in "+timeDelta/1000.0+" sec.");
    }
    
    if (timeDelta >= (aloitusAika+kesto)*1000.0 && isOn) {
      isOn = false;
      control();
      background(255, 0, 0);
      println("Power off! Running for "+(millis()-startTimeStamp)/1000.0+" sec.");
      isWaiting=true;
    }
  
}  

void control() {
  if (isOn) { 
    dmxOutput.set(1, tuulikoneVoimakkuus);
    background(0, 255, 0);
  } else {
    dmxOutput.set(1, 0);
    background(255, 0, 0);
  }
}

void mousePressed() { 
  timeStamp=millis();
  println("Mouse triggered at: "+timeStamp);
}
