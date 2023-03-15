#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_unifont_t_chinese2);
  u8g2.enableUTF8Print();
}

void loop() {
  String str1 = "你好国zhang";
  String str2 = "87";

  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("Hello World!");
  u8g2.setCursor(0, 40);
  u8g2.print((millis() % 100) < 50 ? str1.c_str() : String(str1 + str2).c_str());
  // u8g2.drawStr(0, 60, String(millis()).c_str());
  u8g2.sendBuffer();

  delay(10);
}