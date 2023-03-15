#include <U8g2lib.h>
#include "pic.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop() {  
  u8g2.firstPage();  
  do {
    draw();
  } while(u8g2.nextPage());
  
  delay(1000);
}

void draw(){      
  u8g2.drawXBMP(0, 0, bitmap_width, bitmap_height, bitmap_bits); // 印出圖形(x, y, w, h, bitmap)
}