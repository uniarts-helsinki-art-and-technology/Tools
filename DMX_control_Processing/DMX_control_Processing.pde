import dmxP512.*;
import processing.serial.*;

int lightIntensity = 0; // between 0 - 255, minimi teho 0, maksimi teho 255

DmxP512 dmxOutput;
int universeSize=128;

boolean LANBOX=false;
String LANBOX_IP="192.168.1.77";

boolean DMXPRO=true;
String DMXPRO_PORT="/dev/tty.usbserial-1431410";//case matters ! on windows port must be upper cased.
int DMXPRO_BAUDRATE=115000;
int lightIncrement = 1;

void setup() {
  size(400, 400);  
  background(255, 255, 255);
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
  
  if (lightIntensity>254) {    
    lightIncrement *= -1;
  }

  if (lightIntensity<0) {
    lightIncrement *= -1;
  }    
  
  lightIntensity += lightIncrement;
  
  println("lightIntensity " + lightIntensity + " lightIncrement " + lightIncrement);
  
  dmxOutput.set(1, lightIntensity);
  background(lightIntensity);
}  
