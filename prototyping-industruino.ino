#include <UC1701.h>

static UC1701 lcd;

const int PIN_LCD_BACKLIGHT = 26; 

void setup() {
  SerialUSB.begin(115200);

  lcd.begin();
  analogWrite(PIN_LCD_BACKLIGHT, 255);
  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Industruino PROTO"); 
}

void loop() {
}
