/**
 * LoadFile 1
 * 
 * Loads a text file that contains two numbers separated by a tab ('\t').
 * A new pair of numbers is loaded each frame and used to draw a point on the screen.
 */

import processing.sound.*;

SinOsc sine;

float freq=400;

String[] lines;
int index = 0;
int indexLine = 0;
int lineNumber = 0;
int letterNumber = 0;
char currentChar = 'x';

void setup() {
  size(400, 400);
  fill(255);
  frameRate(5);
  textSize(30);
  textAlign(CENTER, CENTER);
  
  lines = loadStrings("AVPR1A-spaces.txt");

  //Create the Sine Oscillator. 
  sine = new SinOsc(this);

  //Start the Sine Oscillator. 
  sine.play();
  sine.amp(0.3);
}

void draw() {
    background(0);

  // keep the index inside the limited to  the number of lines
  if (index < lines.length) {

    // create array of strings
    String[] pieces = split(lines[index], '\t');


    // loop through lines
    if (lineNumber<pieces[indexLine].length()) {

      // get the letters from each line
      char[] chars = pieces[indexLine].toCharArray();

      // loop through letters in each line
      if (letterNumber<chars.length) {
        println(chars[letterNumber]);
        char currentLetter = chars[letterNumber];
        if (currentLetter=='a') {
          freq = 440;
        } else if (currentLetter=='g') {
          freq = 391.995;
        } else if (currentLetter=='c') {
          freq = 263;
        } else {
          freq = 40;
        }
        currentChar=currentLetter;
        // go to the next letter
        letterNumber++;
      } else {
        // start from the first letter when line is finished
        letterNumber=0;
      }
      // go to the next line
      lineNumber++;
    } else {
      
      // start from the first line
      lineNumber=0;
    }
    
    
    // Go to the next line for the next run through draw()
    index++;
  } else {
    
    index = 0;
  }
  text(currentChar,width/2, height/2);
  sine.freq(freq);
}