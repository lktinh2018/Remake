void initTicker() {
  printToLCD.attach(10, updateLCD);
}

void updateLCD() {
  lcd.clear();
  digitalClockDisplay();
  readDHT();
  printDHT();
}
