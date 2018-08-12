#include <HTTPClient.h>

WiFiServer server(80);
WiFiClient client;

void initWebserver() {
  Serial.println("Init Webserver");
  myDelay(100);
  server.begin();
  myDelay(100);
  Serial.println("Init Webserver End");
  
}



void getWeather(String city) {
  Serial.println("start getWeather()");
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin("https://openweathermap.org/find?q=" + city); //HTTP
  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header

  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      //Serial.println(payload);
      payload = "";
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  weatherImage = weatherImage + 1;
  if (weatherImage > 2) {
    weatherImage = 0;
  }
}



String getHTMLParams(String text, String search)
{
  if (text.indexOf(search)) {
    String s = text.substring(text.indexOf(search) + search.length(), text.length());
    return s.substring(0, s.indexOf("&"));
  } else {
    return "";
  }
}


// if you get a client,
void handleHTTP(WiFiClient client) {
  Serial.println("New Client.");           // print a message out the serial port
  if (client.available()) {             // if there's bytes to read from the client,
    String req = client.readStringUntil('\r');
    Serial.print("#");
    //char c = client.read();             // read a byte, then
    Serial.println(req);
    //if (currentLine.length() == 0 || currentLine.indexOf("GET / ") >= 0) {
    if (req.indexOf("GET /index.html") != - 1 || req.indexOf("GET / ") != - 1) {
      //if (currentLine.indexOf("GET /index.htm") >= 0 || currentLine.indexOf("GET / ") >= 0) {
      Serial.println("Output page ....");
      // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
      // and a content-type so the client knows what's coming, then a blank line:


      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println();
      client.println("<html><head><meta charset=\"utf-8\"><title>ESP 16x8 Display</title><script>function getMode(mode) {");
      client.println("  var request = new XMLHttpRequest();");
      client.println("  var city = document.getElementById('city').value;");
      client.println("  var ledtext = document.getElementById('ledtext').value;");
      client.println("  var countdown = document.getElementById('countdown').value;");
      client.println("  request.open('GET', '/?mode='+mode+'&text=' + ledtext + '&city='+city+'&countdown='+countdown+'&');");
      client.println("  request.send();");
      client.println("  console.log('getMode');");
      client.println("}</script></head>");
      client.println("<body><p>Update your ESP display</p><table>");
      client.println("<tr><td></td><td><input type=\"submit\" class=\"button\" onclick=\"getMode('TIME');\" value=\"Show time!\" /></td></tr>");
      client.println("<tr><td><input type=\"text\" name=\"city\" id=\"city\" placeholder=\"City\" /></td>");
      client.println("<td><input type=\"submit\" class=\"button\" onclick=\"getMode('WEATHER');\" value=\"Show weather!\" /></td></tr>");
      client.println("<tr><td><input type=\"text\" name=\"text\" id=\"ledtext\" placeholder=\"Message\" /></td>");
      client.println("<td><input type=\"submit\" class=\"button\" onclick=\"getMode('TEXT');\" value=\"Show Text!\" /></td></tr>");
      client.println("<tr><td><input type=\"text\" name=\"countdown\" id=\"countdown\" placeholder=\"Countdown\" /></td>");
      client.println("<td><input type=\"submit\" class=\"button\" onclick=\"getMode('COUNTDOWN');\" value=\"Countdown\" /></td></tr>");
      client.println("<tr><td></td><td><input type=\"submit\" class=\"button\" onclick=\"getMode('WHITE');\" value=\"White\" /></td></tr>");
      client.println("<tr><td></td><td><input type=\"submit\" class=\"button\" onclick=\"getMode('RAINBOW');\" value=\"Rainbow\" /></td></tr>");
      client.println("<tr><td></td><td><input type=\"submit\" class=\"button\" onclick=\"getMode('BLACK');\" value=\"Black\" /></td></tr>");
      client.println("<tr><td></td><td><input type=\"submit\" class=\"button\" onclick=\"getMode('DEEPSLEEP');\" value=\"DeepSleep\" /></td></tr>");
      client.print("<tr><td>Your IP:");
      client.print(WiFi.localIP().toString());
      client.println("</td></tr>");
      client.println("</table></body></html>");



      /*
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();
        client.println("<frameset>");
        client.print("<frame src=\"http://com2u.de/ESPLEDDisplay.html?ip=");
        client.print(WiFi.localIP());
        client.println("\">");
        client.println("</frameset>");
      */
      // The HTTP response ends with another blank line:
      client.println();
      // break out of the while loop:
      client.flush();
      //break;
    }
    Serial.println("debug: #" + getHTMLParams(req, "mode=") + "#");
    delay(100);
    String modeResult = getHTMLParams(req, "mode=");
    if (modeResult.equals("WEATHER")) {
      newStep = true;
      espmode = WEATHER;
      Serial.println("Next Mode = WEATHER");
      String city = getHTMLParams(req, "city=");
      getWeather(city);
    } else if (modeResult.equals("TIME")) {
      espmode = TIME;
      Serial.println("Next Mode = TIME");

    } else if (modeResult.equals("TEXT")) {
      newStep = true;
      String text = getHTMLParams(req, "text=");
      scrollText = text;
      espmode = TEXT;
      Serial.println("Next Mode = TEXT");

    } else if (modeResult.equals("COUNTDOWN")) {
      newStep = true;
      String text = getHTMLParams(req, "countdown=");
      countDownFrom = text.toInt();
      countDownStarted == false;
      espmode = COUNTDOWN;
      Serial.println("Next Mode = COUNTDOWN ");
      Serial.println(countDownFrom);
    } else if (modeResult.equals("WHITE")) {
      newStep = true;
      espmode = LIGHTWHITE;
      Serial.println("Next Mode = WHITE");
    } else if (modeResult.equals("BLACK")) {
      newStep = true;
      espmode = LIGHTBLACK;
      Serial.println("Next Mode = BLACK");
    } else if (modeResult.equals("RAINBOW")) {
      newStep = true;
      espmode = LIGHTRAINBOW;
      Serial.println("Next Mode = WHITE");
    } else if (modeResult.equals("DEEPSLEEP")) {
      newStep = true;
      espmode = DEEPSLEEP;
      Serial.println("Next Mode = DEEPSLEEP");
    }
    client.flush();
  }
}


// Loop on core 0
void webserver(void * pvParameters) {
  initWebserver();
  while (true) {
    client = server.available();   // listen for incoming clients
    if (client) {
      Serial.println("Handle HTTP");
      handleHTTP( client);
    }
    delay(100);
  }
}

