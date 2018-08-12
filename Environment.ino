#define BUZZER 12

int threshold = 40;
bool touch1detected = false;
int ispressedCounter = false;
bool touch2detected = false;
bool touch3detected = false;
bool touch4detected = false;

void initTouch() {
  touchAttachInterrupt(T0, gotTouch1, threshold);
  touchAttachInterrupt(T2, gotTouch2, threshold);
  touchAttachInterrupt(T3, gotTouch3, threshold);
  touchAttachInterrupt(T5, gotTouch4, threshold);
}


void gotTouch1() {
  touch1detected = true;
}

void gotTouch2() {
  if (espmode == HACKERSTACKER) {
    espmode = TIME;
  } else {
    espmode = (ESPModes)(espmode + 1);
  }
  touch2detected = true;
}

void gotTouch3() {
  touch3detected = true;
}

void gotTouch4() {
  touch4detected = true;
}

bool nextStep() {
  if (newStep) {
    newStep = false;
    LED(BLACK);
    delay(10);
    countDownStarted = false;
    return true;
  }
  if (touch1detected && touchRead( T0 ) >= threshold)
  {
    touch1detected = false;
    Serial.println("T0");
    return true;
  }
  if (touch2detected && touchRead( T2 ) >= threshold)
  {
    touch2detected = false;
    LED(BLACK);
    Serial.print("Next step ");
    Serial.println(touchRead( T2 ));
    return true;
  }
  if (touch3detected && touchRead( T3 ) >= threshold)
  {
    touch3detected = false;
    Serial.println("T3");
    return true;
  }
  if (touch4detected && touchRead( T5 ) >= threshold)
  {
    touch4detected = false;
    Serial.println("T5");
    return true;
  }
  return false;
}

void initBuzzer() {
  #ifdef BUZZER
  pinMode(BUZZER, OUTPUT);           // set pin to input
  #endif
}


void buzzer(int beepTime) {
  #ifdef BUZZER
  for (int i = 0; i < beepTime; i++) {
    myDelay(3);
    digitalWrite(BUZZER, HIGH);
    myDelay(3);
    digitalWrite(BUZZER, LOW);
  }
  #else
  Serial.println("BUZZER");
  #endif
}

void myDelay(int waitTime) {
  unsigned long time_now = 0;
  time_now = millis();
  while (millis() < time_now + waitTime) {
    yield();
  }
}
