void initTimer() {    
  Timer::getInstance()->initialize();
  printToLCD = new WorkScheduler(3000UL, &updateLCD);
}

void loopTimer() {
  Timer::getInstance()->update();

  printToLCD->update();
  
  Timer::getInstance()->resetTick();
}

void updateLCD() {
  readDS1307();
  digitalClockDisplay();
  readDHT();
  printDHT();
}

