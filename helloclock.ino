// Simple clock based on Hello World and Font examples from MajicDesigns
// libraries. Uses DS3231 RTC. Offline clock without internet connection.
//
// Font editor at https://pjrp.github.io/MDParolaFontEditor
//
// Use something to set DS3231 first.
//

#include <MD_DS3231.h>
#include <MD_Parola.h>

#include "Font_Data.h"

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

// ESP32 C3 supermini
// #define CLK_PIN   4
// #define DATA_PIN  6
// #define CS_PIN    7

// MEGA2560
// #define CLK_PIN   52
// #define DATA_PIN  51
// #define CS_PIN    53

// UNO
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

// Hardware SPI connection
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
// MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Some settings needed to display.
// These may help you if you change fonts.
void setup(void) {
  P.begin();
  P.setFont(digit);               // Font in Font_Data.h
  P.setCharSpacing(1);            // Spacing between characters as pixels.
  P.setTextAlignment(PA_CENTER);  // Text alignment
  P.setIntensity(0);              // Brightnes 0-15
}

char buf[20];
unsigned long previousMillis = 0;
const long interval = 500;
bool toggle = false;

// Here comes the clock
void loop(void) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    RTC.readTime();
    if (toggle) {
      sprintf(buf, "%02d:%02d", RTC.h, RTC.m);
    } else {
      sprintf(buf, "%02d %02d", RTC.h, RTC.m);
    }
    P.print(buf);
    toggle = !toggle;
  }
}
