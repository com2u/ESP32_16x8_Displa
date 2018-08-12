const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
bool timeInSync = false;
bool updateStripe = false;

void initTime() {
  if (!timeInSync) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  }
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    myDelay(1000);
    return;
  }
}

String getDisplayTime() {
  String s = "";
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time 2");
    myDelay(1000);
    return "";
  }
  timeInSync = true;
  s += String(timeinfo.tm_hour);
  s += ":";
  if (timeinfo.tm_min < 10) {
    s += "0";
  }
  s += String(timeinfo.tm_min);
  return s;
}
