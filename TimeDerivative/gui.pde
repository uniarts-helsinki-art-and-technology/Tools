void drawUI(){
  
  // UI INFO
  fill(0);
  noStroke();
  rect(0, height-40, width, 40);
  fill(128);
  text("fps: "+frameRate, 5, height-35);
  text("Press 1,2,3,4,5 to test different modes, c to capture ref frame, q to quit", 5, height-20);
  text("Settings (txt): quality (0-100): "+filePathToSaveVideo[2]+" save to: "+filePathToSaveVideo[0], 5, height-5);
  if(recording){
      text("RECORDING", 50, 35);
      stroke(128);
      fill(128,0,0);
      ellipse(30,30,20,20);
  }
  
}