void initLCD() {
  Wire.begin(2, 0);
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, degree);
}

void digitalClockDisplay() {
  //Digital clock display of the time
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
  lcd.setCursor(0, 1);
  lcd.print(day());
  lcd.print(".");
  lcd.print(month());
  lcd.print(".");
  lcd.print(year());
}

void printDigits(int digits) {
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
