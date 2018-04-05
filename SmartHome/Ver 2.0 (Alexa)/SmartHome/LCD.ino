void initLCD() {
  Wire.begin(2, 0);
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, degree);
}
