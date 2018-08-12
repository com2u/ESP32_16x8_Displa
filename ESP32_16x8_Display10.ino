#include <WiFi.h>
#include "time.h"
#define NUM_MATRIXLEDS    128

#ifdef NUM_MATRIXLEDS
  #include<FastLED.h>
  CRGB leds[NUM_MATRIXLEDS];
  byte Cloud[] = {0, 0, 0, 255, 255, 240, 205, 205, 193, 0, 0, 0, 0, 0, 0, 255, 165, 0, 0, 0, 0, 0, 0, 0, 255, 255, 240, 255, 255, 240, 255, 255, 240, 255, 255, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 205, 205, 193, 255, 255, 240, 205, 205, 193, 205, 205, 193, 255, 165, 0, 255, 165, 0, 0, 0, 0, 255, 255, 0, 205, 205, 193, 205, 205, 193, 255, 165, 0, 255, 165, 0, 255, 255, 0, 255, 165, 0, 0, 0, 0, 0, 0, 0, 205, 205, 193, 205, 205, 193, 205, 205, 193, 205, 205, 193, 255, 255, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 240, 255, 255, 240, 205, 205, 193, 205, 205, 193, 255, 165, 0, 0, 0, 0, 255, 165, 0, 0, 0, 0, 255, 255, 240, 255, 255, 240, 255, 255, 240, 255, 255, 240, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255, 240, 255, 255, 240, 255, 255, 240, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0};
  byte Sun[] = {0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 255, 255, 0, 255, 255, 0, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 0, 0, 205, 0, 0, 205, 0, 0, 205, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 0, 0, 205, 0, 0, 205, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 0, 0, 205, 0, 0, 205, 0, 0, 205, 255, 255, 0, 255, 255, 0, 255, 255, 0, 255, 255, 0, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 255, 255, 0, 255, 255, 0, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205, 0, 0, 205};
  byte Raindrop[] = {0, 0, 0, 24, 116, 205, 24, 116, 205, 24, 116, 205, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 116, 205, 28, 134, 238, 28, 134, 238, 28, 134, 238, 28, 134, 238, 28, 134, 238, 0, 0, 0, 0, 0, 0, 28, 134, 238, 28, 134, 238, 191, 239, 255, 28, 134, 238, 28, 134, 238, 28, 134, 238, 28, 134, 238, 28, 134, 238, 28, 134, 238, 191, 239, 255, 191, 239, 255, 191, 239, 255, 28, 134, 238, 28, 134, 238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 28, 134, 238, 28, 134, 238, 28, 134, 238, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#endif

const char* ssid[] =     {  "muccc.legacy-2.4GHz", "muenchen.freifunk.net",  "Cafeteria" };
const char* password[] = {  "haileris"           , ""                     ,  "$eidenader"};

#ifdef __AVR__
  #include <avr/power.h>
#endif

int weatherImage = 0;
String scrollText = "Hello World!";
int countDownFrom = 50;
boolean countDownStarted = false;
boolean newStep=true;

enum ESPModes {
  INIT = 0,
  TIME = 1,
  TEXT = 2,
  COUNTDOWN = 3,
  LIGHTWHITE = 4,
  LIGHTRAINBOW = 5,
  LIGHTBLACK = 6,
  HACKERSTACKER = 7,
  DEEPSLEEP = 8,
  WEATHER = 9
};
ESPModes espmode = INIT;

enum LEDModes {
  BLACK,
  WHITE,
  RAINBOW
};


void setup() {
  espmode = TIME;
  Serial.begin(115200);
  delay(200); // give me time to bring up serial monitor
  Serial.println("ESP32_16x8_Display");
  initWIFI();
  initTouch();
  initBuzzer();
  initDeepSleep();
  initTime();
  initLED();
  initHackerStacker();
  // Webserver will run on other core (0)
  xTaskCreatePinnedToCore(webserver, "coreTask", 10000, NULL, 0, NULL, 0);
}

void loop() {
  nextStep();
  switch (espmode) {
    case DEEPSLEEP:
      Serial.println("Loop DeepSleep");
      startSleep();
      break;
    case COUNTDOWN:
      doCountDown(countDownFrom);
      break;
    case TIME:
      //init and get the time
      initTime();
      LEDText(getDisplayTime(), true);
      myDelay(1000);
      break;
    case TEXT:
      LEDText(scrollText, true);
      LEDShow();
      myDelay(1000);
      break;
    case LIGHTWHITE:
      LED(WHITE);
      myDelay(1000);
      break;
    case LIGHTRAINBOW:
      LED(RAINBOW);
      myDelay(1000);
      break;
    case LIGHTBLACK:
      LED(BLACK);
      myDelay(1000);
      break;
    case HACKERSTACKER:
      //Serial.println("HackerStacker");
      HackerStacker();
      break;
    case WEATHER:
      LED(BLACK);
      switch (weatherImage) {
        case 0:
          Serial.println("display WEATHER Cloud");
          displayWeather(Cloud);
          break;
        case 1: Serial.println("display WEATHER Sun");
          displayWeather(Sun);
          break;
        case 2: Serial.println("display WEATHER Rain");
          displayWeather(Raindrop);
          break;
      }
      break;
    default:
      Serial.print("Unkown Mode");
      myDelay(5000);
  }
}

void initWIFI() {
  //connect to WiFi
  int networkNo = 0;
  int retries = 12;
  int retry = 0;
  //attempt to connect to the wifi if connection is lost
  if (WiFi.status() != WL_CONNECTED) {

    // Try several WIFI Networks
    for (networkNo = 0; networkNo < 8; networkNo++) {
      Serial.print("Connecting ");
      Serial.print(networkNo);
      Serial.print(" of ");
      Serial.print(sizeof(ssid));
      Serial.print(" to ");
      Serial.println(ssid[networkNo]);
      delay(100);
      WiFi.begin(ssid[networkNo], password[networkNo]);
      WiFi.setHostname("ESP32LED");
      for (retry = 0; retry < retries; retry++) {
        if (WiFi.status() == WL_CONNECTED) {
          break;
        } else {
          buzzer(3);
          Serial.print(".");
          delay(1000);
        }
      }
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected");
        break;
      }
      Serial.println("Try another AP");
      WiFi.mode(WIFI_OFF);
      delay(2000);
      WiFi.mode(WIFI_STA);
    }
  }
  // Create Acces Point when no WIFI found
  if (retry == retries) {
    Serial.println(WiFi.softAP("ESPsoftAP_01") ? "Ready" : "Failed!");
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
  }
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


