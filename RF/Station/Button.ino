void initButton() {
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(1, changRelayState, FALLING); 
}

void changRelayState() {
  activatedRelay = !activatedRelay;
  if(activatedRelay)
    activeRelay();
  else
    deactiveRelay();
}

