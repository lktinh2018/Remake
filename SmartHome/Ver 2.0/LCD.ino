void initLCD() {
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, degree);
}
