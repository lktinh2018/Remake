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
//  readDS1307();
  lcd.clear();
  digitalClockDisplay();
//  readDHT();
  printDHT();
}

