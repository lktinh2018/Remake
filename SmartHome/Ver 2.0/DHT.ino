void initDHT() {
  dht.begin();
}

void readDHT() {
  t = dht.readTemperature();
  h = dht.readHumidity();
}

void printDHT() {
  lcd.setCursor(10,0);
  lcd.print("T:");
  lcd.print(t);
  lcd.write(0);
  lcd.print("C     ");
  lcd.setCursor(10,1);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");
}

