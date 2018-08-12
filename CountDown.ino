int currentTick = 0;

void initCountDown() {
  countDownStarted = false;
}

void doCountDown(int initValue) {
  String s = "";
  if (!countDownStarted) {
    Serial.println("Init CountDown");
    currentTick = initValue;
    LED(BLACK);
    myDelay(20);
    countDownStarted = true;
  }
  if (currentTick > 0) {
    s = String(currentTick);
    LEDText(s+"  ", false);
    currentTick--;
  } else {
    LED(BLACK);
    buzzer(100);
  }
  Serial.println(currentTick);
  myDelay(1000);
}

