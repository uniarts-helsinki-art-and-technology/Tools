void setupControls() {

  cp5 = new ControlP5(this);
  cp5.addFrameRate().setInterval(10).setPosition(0, height - 10);


  cp5.addTextfield("startTimeInput")
    .setPosition(130, 10)
    .setSize(30, 20)
    .setAutoClear(false)
    .setLabel("START (sec)")
    ;

  cp5.addTextfield("endTimeInput")
    .setPosition(180, 10)
    .setSize(30, 20)
    .setAutoClear(false)
    .setLabel("END")
    ;



  // create a toggle
  cp5.addButton("pause").setLabel("PAUSED")
    .setPosition(10, 70)
    .setSize(50, 50)
    .setColorBackground(color(255, 0, 50))
    .setColorForeground(color(240, 0, 0))
    .setColorActive(color(250, 250, 50));


  // create a new button with name 'buttonA'
  cp5.addButton("restart")
    .setPosition(80, 70)
    .setSize(50, 50).setColorBackground(color(51, 225, 240))
    .setColorActive(color(250, 250, 50))
    .setColorForeground(color(71, 163, 240));
  ;

  cp5.addButton("stop")
    .setPosition(timeTextX, 10)
    .setSize(30, 30).setColorBackground(color(51, 225, 240))
    .setColorActive(color(250, 250, 50))
    .setColorForeground(color(71, 163, 240));
  ;

  cp5.addToggle("fScreen")
    .setValue(true)
    .setPosition(60, 10)
    .setSize(30, 30);

  cp5.addSlider("alphaValue")
    .setPosition(10, 150)
    .setSize(300, 10)
    .setRange(0., 1.)
    .setValue(1.0)
    ;

  cp5.addSlider("seek")
    .setPosition(10, 170)
    .setSize(300, 10)
    .setRange(0, 100)
    .setValue(0)
    ;
}


void controlEvent(ControlEvent theEvent) {
  if (theEvent.isAssignableFrom(Textfield.class)) {
     println("controlEvent: accessing a string from controller '"
            +theEvent.getName()+"': "
            +theEvent.getStringValue()
            );
    if (theEvent.getName().equals("startTimeInput")) {
      startTime = int(theEvent.getStringValue());
    }

    if (theEvent.getName().equals("endTimeInput")) {
      endTime = int(theEvent.getStringValue());
    }
  }
}
