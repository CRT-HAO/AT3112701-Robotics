#include <Arduino.h>
#include <U8g2lib.h>
#include "u8g2_font_unifont.h"
#include "lyrics.h"
#include "song.h"

#define BUZZER_PIN_1 23
#define BUZZER_PIN_2 32
#define BUZZER_PIN_3 19
#define BUZZER_PIN_4 18
#define BUZZER_PWM_CHANNEL_1 0
#define BUZZER_PWM_CHANNEL_2 1
#define BUZZER_PWM_CHANNEL_3 2
#define BUZZER_PWM_CHANNEL_4 2
#define BUZZER_PWM_RESOLUTION 32

const uint8_t SCREEN_STR_WIDTH = 26;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN_1, OUTPUT);
  pinMode(BUZZER_PIN_2, OUTPUT);
  pinMode(BUZZER_PIN_3, OUTPUT);
  pinMode(BUZZER_PIN_4, OUTPUT);

  ledcSetup(BUZZER_PWM_CHANNEL_1, 0, BUZZER_PWM_RESOLUTION);
  ledcAttachPin(BUZZER_PIN_1, BUZZER_PWM_CHANNEL_1);

  ledcSetup(BUZZER_PWM_CHANNEL_2, 0, BUZZER_PWM_RESOLUTION);
  ledcAttachPin(BUZZER_PIN_2, BUZZER_PWM_CHANNEL_2);

  ledcSetup(BUZZER_PWM_CHANNEL_3, 0, BUZZER_PWM_RESOLUTION);
  ledcAttachPin(BUZZER_PIN_3, BUZZER_PWM_CHANNEL_3);

  ledcSetup(BUZZER_PWM_CHANNEL_4, 0, BUZZER_PWM_RESOLUTION);
  ledcAttachPin(BUZZER_PIN_4, BUZZER_PWM_CHANNEL_4);

  u8g2.begin();
  u8g2.setFont(u8g2_font_unifont);
  u8g2.enableUTF8Print();
}

const uint64_t START_TIME = micros();
uint32_t last_play = 0;
String last_text;
String last_time_text;

void loop() {

  // Play Song
  uint32_t play[4] = { 0 };
  size_t c = 0;
  uint64_t short_time = INFINITY;

  uint64_t time = micros() - START_TIME;

  for(size_t i = 0; i < SONG_LENGTH; i++) {
    if(time >= SONG[i][1] && time <= SONG[i][2]) {
      if(c < 4) {
        play[c] = SONG[i][0];
        if((SONG[i][2] - SONG[i][1]) < short_time)
          short_time = (SONG[i][2] - SONG[i][1]);
        c++;
      }
    }
  }

  uint32_t play_sum = 0;  
  for(size_t i = 0; i < 4; i++) {
    play_sum += play[i];
  }
  if(play_sum != last_play) {
    Serial.print(time);
    Serial.print(", ");
    for(size_t i = 0; i < 4; i++) {
      ledcWriteTone(i, play[i]);
      Serial.print(play[i]);
      Serial.print(", ");
    }
    Serial.println();
    last_play = play_sum;
  }


  // Show Lyrics
  String text;

  for(size_t i = 0; i < LYRICS_SIZE - 1; i++) {
    if(time >= LYRICS[i].time && time < LYRICS[i + 1].time) {
      text = LYRICS[i].text;
      break;
    }
  }

  char time_text_mins[4];
  char time_text_secs[4];
  String time_text;
  uint64_t mins = (time / 1000000) / 60;
  uint64_t secs = (time / 1000000) % 60;
  sprintf(time_text_mins, "%02lu", mins);
  sprintf(time_text_secs, "%02lu", secs);
  time_text = String(time_text_mins) + char(':') + String(time_text_secs);

  if(text != last_text || time_text != last_time_text) {
    u8g2.clearBuffer();
    u8g2.setCursor(0, 15);
    u8g2.print(time_text);
    u8g2.setCursor(0, 40);
    u8g2.print(text.substring(0, SCREEN_STR_WIDTH - 1));
    u8g2.setCursor(0, 60);
    u8g2.print(text.substring(SCREEN_STR_WIDTH - 1, SCREEN_STR_WIDTH + SCREEN_STR_WIDTH - 1));
    u8g2.sendBuffer();

    last_text = text;
    last_time_text = time_text;
  }
  
}
