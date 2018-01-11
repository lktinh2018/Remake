void initRTC() {
  Wire.begin(2, 0);
  //setTime(16, 56, 00, 4, 18, 8, 17); // 12:30:45 CN 08-02-2015
}

void readDS1307() {
    Wire.beginTransmission(DS1307);
    Wire.write((byte)0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307, NumberOfFields);
    
    second = bcd2dec(Wire.read() & 0x7f);
    minute = bcd2dec(Wire.read() );
    hour   = bcd2dec(Wire.read() & 0x3f); // 24h mode
    wday   = bcd2dec(Wire.read() );
    day    = bcd2dec(Wire.read() );
    month  = bcd2dec(Wire.read() );
    year   = bcd2dec(Wire.read() ); 
}


void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr) {
    Wire.beginTransmission(DS1307);
    Wire.write(byte(0x00)); // đặt lại pointer
    Wire.write(dec2bcd(sec));
    Wire.write(dec2bcd(min));
    Wire.write(dec2bcd(hr));
    Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
    Wire.write(dec2bcd(d)); 
    Wire.write(dec2bcd(mth));
    Wire.write(dec2bcd(yr));
    Wire.endTransmission();
}

int bcd2dec(byte num) {
    return ((num/16 * 10) + (num % 16));
}

int dec2bcd(byte num) {
    return ((num/10 * 16) + (num % 10));
}
