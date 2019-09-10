void updateTimeText() {
  
  timeTextSeconds = (elapsedTime ) % 60;
  timeTextMinutes = (elapsedTime ) / 60;
  timeText = nf(timeTextMinutes, 2) + ':' + nf(timeTextSeconds, 2) ;
}

// this is called once per second when the timer is running
void onTickEvent(CountdownTimer t, long timeLeftUntilFinish) {
  ++elapsedTime;
  updateTimeText();
}

// this will be called after the timer finishes running for an hour 
void onFinishEvent(CountdownTimer t) {
  exit();
}
