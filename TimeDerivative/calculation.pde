
void calculateDifference(Capture _cameraInput, int[] referenceArray, String METHOD) {
  int d = 0;
  int a = 0;
  int b = 0;
  total = 0;
  int x = 0;
  int y = 0;
  int r = 0;
  int g = 0;
  for (int i = 0; i < numPixels; i++) { 

    // flip image horizontally?
    int loc = i;
    if (mirror) {  
      i = y*width + (width - x - 1);
    } 

    // Extract the green channel values of the current pixel's color
    a = (_cameraInput.pixels[i] >> 8) & 0xFF;
    b = (referenceArray[i] >> 8) & 0xFF;

    if (METHOD.compareTo("ABSOLUTE")==0)
    {
      d = abs(a-b);
    } else if (METHOD.compareTo("SQUAREROOT")==0)
    {
      d = int(pow(sqrt(float(a)-float(b)), 2));
    } else if (METHOD.compareTo("HEATMAP")==0)
    {
        d = a-b;
       r =  int(map(d, -255,255,0,255));
       g =  int(map(d, -255,255,255,0));
    }
    // other methods of computing? add here...

    if (d>threshold || !useThreshold) {
      // write new values to pixel array
      if (METHOD.compareTo("HEATMAP")==0) {
        pixels[i] = 0xFF000000 | (r << 16) | (g << 8) | 128;
        total+=r;
      } else {
        pixels[i] = 0xFF000000 | (d << 16) | (d << 8) | d;
        total+=d; // update to avoid flickering
      }
    } else {
      pixels[i] = 0xFF000000 | (0 << 16) | (0 << 8) | 0;
    }

    if (frameToFrameDifference) {
      // save current values to pixel array for frame diffence
      previousFrame[loc] = 0xFF000000 | (a << 16) | (a << 8) | a;
    }
    if (mirror) {
      x++;
      if (x>=width) { 
        x=0; 
        y++;
      }
    }
  }
}