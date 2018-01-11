void initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, degree);
}

void digitalClockDisplay() {
  lcd.clear();
  lcd.print(hour);
  printDigits(minute);
  printDigits(second);
  lcd.setCursor(0, 1);
  lcd.print(day);
  lcd.print("-");
  lcd.print(month);
  lcd.print("-");
  lcd.print(year); 
}

void printDigits(int digits){
  lcd.print(":");      
  if(digits < 10)
      lcd.print('0');
  lcd.print(digits);
}
