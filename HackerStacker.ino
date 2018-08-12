#ifdef NUM_MATRIXLEDS
#define MAXBARWIDTH 4
int barDirection = 1;
int xPos = 0;
int level = 0;
int barWidth = 4;
boolean gameEnd = false;

void initHackerStacker() {
  LED(BLACK);
  buzzer(100);
  xPos = 0;
  level = 0;
  barWidth = 4;
  touch1detected = false;
  gameEnd = false;
}

void HackerStacker() {

  if (level > 15 | gameEnd == true) return;
  if (touch1detected && touchRead( T0 ) >= threshold)
  {
    finalizeLine();
    touch1detected = false;
    level++;
    barWidth = MAXBARWIDTH - (level / 5);
    Serial.println("Touch 1 detected");

  } else {

    while (!touch1detected) {

      if (touch1detected) {
        Serial.println("Finalize line");
        finalizeLine();
        return;
      }
      if (xPos >= 8 - barWidth) {
        barDirection = -1;
        buzzer(10);
      }
      if (xPos <= 0) {
        barDirection = 1;
        buzzer(10);
      }
      xPos = (xPos + barDirection) ;
      //Serial.println(xPos + level * 8);
      for ( int k = 0; k < 8; k++) {
        leds[k +  level * 8] = CRGB::Black;
        //strip.setPixelColor(, 0, 0, 0);
      }
      for ( int k = 0; k < barWidth; k++) {
        leds[k + xPos + level * 8] = CRGB::Red;
        //strip.setPixelColor(k + xPos + level * 8, 20, 0, 0);
      }
      //strip.setPixelColor((((xPos - direction) % WIDTH) + level * 8), 0, 0, 0);
      LEDShow();
      myDelay(210 - (level * 12));

    }
  }

}

void finalizeLine() {

  int matchCount = 0;
  for ( int k = 0; k < 8; k++)  {
    //Serial.print(strip.getPixelColor(k + xPos + (level - 1) * 8 ));
    //Serial.print(" ");
    if (level == 0 || (k > xPos && k < (xPos + barWidth))) {
      leds[k  + level * 8] = CRGB::Green;
      matchCount++;
      Serial.print("*");
      //strip.setPixelColor(k + xPos + level * 8, 0, 50, 0);
    } else {
      leds[k + level * 8] = CRGB::Black;
      //strip.setPixelColor(k + xPos + level * 8, 0, 0, 8);
      Serial.print(".");
    }
  }
  Serial.println("");
  if (matchCount == 0) {
    gameEnd == true;
  }
  LEDShow();
  myDelay(30);
  
}

#else
void initHackerStacker() {
  Serial.println("initHackerstacker");

}
void HackerStacker() {
  Serial.println("initHackerstacker");
}

#endif
