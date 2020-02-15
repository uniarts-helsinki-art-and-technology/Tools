import processing.video.*; // Processing video library from Camera capture
import com.hamoid.*; // Video recording library, uses FFMPEG

VideoExport videoExport;
Capture cameraInput;

// SETTINGS
// MODIFY settings > settings.txt outside Processing
boolean recording = false;
boolean mirror = false; // TO DO: Add horizontal flipping,
boolean frameToFrameDifference = true;
boolean useThreshold = false;
int threshold = 0;
int method = 3; // CHOOSE THE DEFAULT METHOD HERE (1-5)

// DON*T CHANGE FOLLOWING
String[] filePathToSaveVideo;
int numPixels;
int total = 0;
int[] referenceFrame;
int [] previousFrame;
boolean captureFrameInSetup = true;


void setup() {
  size(1280, 720); // Default camera ratio, try 640*360 for lower resolution
  //size(640, 360);
  // frameRate(30);
  filePathToSaveVideo = loadStrings("settings/settings.txt");

  videoExport = new VideoExport(this);
  customizeVideoFileSettings(filePathToSaveVideo[2]);

  if (filePathToSaveVideo[1].compareTo("true")==0) {
    recording = true;
  }
  if (recording) {
    videoExport.setMovieFileName(filePathToSaveVideo[0]+"video "+videoID()+".mp4");
    videoExport.startMovie();
  } else {
    videoExport.setDebugging(false);
  }

  cameraInput = new Capture(this, width, height);
  cameraInput.start();  

  // Some buffer matrices for storing pixels
  numPixels = cameraInput.width * cameraInput.height;
  referenceFrame = new int[numPixels];
  previousFrame = new int[numPixels];

  // Make the pixels[] array available for direct manipulation
  loadPixels();
}

void draw() {

  if (cameraInput.available()) {
    background(0);

    // READ CAMERA DATA
    cameraInput.read();
    cameraInput.loadPixels(); 

    // CALCULATE
    switch (method) {
    case 1:
      calculateDifference(cameraInput, referenceFrame, "ABSOLUTE");
      break;
    case 2:  
      calculateDifference(cameraInput, referenceFrame, "SQUAREROOT");
      break;
    case 3: 
      calculateDifference(cameraInput, previousFrame, "ABSOLUTE");
      break;
    case 4:  
      calculateDifference(cameraInput, previousFrame, "SQUAREROOT");
      break;
    case 5:  
      calculateDifference(cameraInput, previousFrame, "HEATMAP");
      break;
    default:
      println("Define method!");
      break;
    }
    if (total>0) updatePixels(); // Skip empty frames before drawing to screen
   
    // RECORD
    if (recording) videoExport.saveFrame();
    if(captureFrameInSetup) { recordStillFrame();captureFrameInSetup=false; } // RUN ONCE IN SETUP

  }
drawUI();
}

void mousePressed() {
  recording = true;
  videoExport.setMovieFileName(filePathToSaveVideo[0]+"video "+videoID()+".mp4");
  videoExport.startMovie();
  println("Start recording...");
}
void mouseReleased() {
  recording = false;
  videoExport.endMovie();
}

void keyPressed() {
  if (key=='c') {
    recordStillFrame();
  }
  if (key == 'q') {
    recording = false;
    videoExport.endMovie();
    if (recording) {
      println("... stopped recording.");
    }
    exit();
  }
  if (key=='1') {
    method = 1;
    frameToFrameDifference = false;
  }
  if (key=='2') {
    method = 2;
    frameToFrameDifference = false;
  }
  if (key=='3') {
    method = 3;
    frameToFrameDifference = true;
  }
  if (key=='4') {
    method = 4;
    frameToFrameDifference = true;
  }
  if (key=='5') {
    method = 5;
    frameToFrameDifference = true;
  }
}


void recordStillFrame() {
  cameraInput.loadPixels();
  arraycopy(cameraInput.pixels, referenceFrame);
}

void customizeVideoFileSettings(String _quality) {
  int q = parseInt(_quality);
  videoExport.setQuality(q, 0);
  videoExport.setLoadPixels(false);
  videoExport.setFrameRate(10);
}

String videoID() {
  String result = year()+"-"+month()+"-"+day()+"-"+hour()+"-"+minute()+"-"+second();
  return result;
}