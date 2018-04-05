void initTimer() {    
  Timer::getInstance()->initialize();
  printToLCD = new WorkScheduler(10000UL, &updateLCD);
}

void loopTimer() {
  Timer::getInstance()->update();

  printToLCD->update();
  
  Timer::getInstance()->resetTick();
}

void updateLCD() {
  lcd.clear();
  digitalClockDisplay();
  readDHT();
  printDHT();
}

