constexpr char ssid[] = "There's no place like home";
constexpr char pass[] = "<password>";

#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

#define TRAMSMISSION_PIN 1
#define MULT 212  // unit of the sample - 212us
#define SUBT 50  // the microseconds used by the rest of the algorithm
#define REPETITIONS 5  // the number of times each signal should be repeated to ensure if was received at least once

constexpr unsigned timeout = 20000;

PROGMEM constexpr char guest_internal_blind_down[] = {10, -20, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -1, 3, -30, 0};
PROGMEM constexpr char guest_internal_blind_up[] =   {10, -20, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -30, 0};
PROGMEM constexpr char guest_internal_blind_stop[] = {10, -20, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -30, 0};

PROGMEM constexpr char guest_external_blind_down[] = {10, -20, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -31, 0};
PROGMEM constexpr char guest_external_blind_up[] =   {10, -20, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -4, 3, -31, 0};
PROGMEM constexpr char guest_external_blind_stop[] = {10, -20, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -1, 3, -31, 0};

PROGMEM constexpr char master_internal_blind_down[] = {10, -20, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -30, 0};
PROGMEM constexpr char master_internal_blind_up[] =   {10, -20, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -4, 2, -30, 0};
PROGMEM constexpr char master_internal_blind_stop[] = {10, -20, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -30, 0};

PROGMEM constexpr char master_external_blind_down[] = {10, -20, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -4, 2, -30, 0};
PROGMEM constexpr char master_external_blind_up[] =   {10, -20, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -1, 2, -30, 0};
PROGMEM constexpr char master_external_blind_stop[] = {10, -20, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 2, -2, 2, -2, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 3, -5, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 2, -2, 2, -2, 2, -2, 3, -5, 3, -5, 3, -4, 2, -30, 0};

////////////////

#include <WiFiNINA.h>
#include <utility/wifi_drv.h>
#include <avr/pgmspace.h>

void setLedColor(unsigned char red, unsigned char green, unsigned char blue) {
  WiFiDrv::analogWrite(RED_LED, red);
  WiFiDrv::analogWrite(GREEN_LED, green);
  WiFiDrv::analogWrite(BLUE_LED, blue);
}

void printWifiStatus() {
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print(F("signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
  Serial.print(F("To see this page in action, open a browser to http://"));
  Serial.println(ip);
}

void printWebPageContent(WiFiClient& client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-type:text/html"));
  client.println();

  client.println(F("<html>"));
  client.println(F("<body>"));
  
  client.println(F("Guest room internal blind control:"));
  client.println(F("<li><a href=\"/guest_internal_blind_down\">guest_internal_blind_down</a></li>"));
  client.println(F("<li><a href=\"/guest_internal_blind_up\">guest_internal_blind_up</a></li>"));

  client.println(F("Guest room external blind control:"));
  client.println(F("<li><a href=\"/guest_external_blind_down\">guest_external_blind_down</a></li>"));
  client.println(F("<li><a href=\"/guest_external_blind_up\">guest_external_blind_up</a></li>"));

  client.println(F("Master bedroom internal blind control:"));
  client.println(F("<li><a href=\"/master_internal_blind_down\">master_internal_blind_down</a></li>"));
  client.println(F("<li><a href=\"/master_internal_blind_up\">master_internal_blind_up</a></li>"));

  client.println(F("Master bedroom external blind control:"));
  client.println(F("<li><a href=\"/master_external_blind_down\">master_external_blind_down</a></li>"));
  client.println(F("<li><a href=\"/master_external_blind_up\">master_external_blind_up</a></li>"));

  client.println(F("</body>"));
  client.println(F("</html>"));

  client.println();
}

void sendCommand(const char* ptr) {
  setLedColor(0, 0, 255);

  for(unsigned char rep = 0; rep < REPETITIONS; ++rep) {
    const char* tmp = ptr;
    
    int val = -1;
    while(val != 0) {
      val = (signed char)pgm_read_byte(tmp);
      digitalWrite(TRAMSMISSION_PIN, val <= 0 ? LOW : HIGH);
      
      if(val != 0) {
        delayMicroseconds(abs(val * MULT) - SUBT);
      }
      ++tmp;
    }
  }

  setLedColor(0, 3, 0);
}

/////////////////////////////////////////////

int status = WL_IDLE_STATUS;
unsigned guest_internal_stop_moving_time = 0;
unsigned guest_external_stop_moving_time = 0;
unsigned master_internal_stop_moving_time = 0;
unsigned master_external_stop_moving_time = 0;

WiFiServer server(80);

void setup() {
  WiFiDrv::pinMode(RED_LED, OUTPUT);
  WiFiDrv::pinMode(GREEN_LED, OUTPUT);
  WiFiDrv::pinMode(BLUE_LED, OUTPUT);

  pinMode(TRAMSMISSION_PIN, OUTPUT);

  Serial.begin(9600);

  setLedColor(10, 0, 0);
  Serial.println(F("Starting wifi..."));
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    setLedColor(255, 0, 0);
    while (true);       // don't continue
  }  

  while (status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to Network named: "));
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  setLedColor(40, 0, 0);

  while(status != WL_CONNECTED) {
    status = WiFi.status();
    delay(1000);
  }
  
  printWifiStatus();

  setLedColor(60, 0, 0);
  server.begin();

  setLedColor(0, 3, 0);
}

void sendSignal(unsigned& moving_time, const char* do_signal, const char* stop_signal, const char*& to_send) {
  if(millis() > moving_time) {
    to_send = do_signal;
    moving_time = millis() + timeout;
  } else {
    to_send = stop_signal;
    moving_time = 0;
  }
}

String currentLine;

void loop() {
  WiFiClient client = server.available();

  const char* toSend = nullptr;

  if (client) {
    Serial.println(F("-- new client --"));
    currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            printWebPageContent(client);
            break;
          } else {
            // one new line character - clear the current content
            currentLine = "";
          }
        } 
        
        else if (c != '\r') {
          currentLine += c;
        }

        if(currentLine.endsWith(F("GET /guest_internal_blind_down"))) {
          sendSignal(guest_internal_stop_moving_time, guest_internal_blind_down, guest_internal_blind_stop, toSend);
        }
        if(currentLine.endsWith(F("GET /guest_internal_blind_up"))) {
          sendSignal(guest_internal_stop_moving_time, guest_internal_blind_up, guest_internal_blind_stop, toSend);
        }

        if(currentLine.endsWith(F("GET /guest_external_blind_down"))) {
          sendSignal(guest_external_stop_moving_time, guest_external_blind_down, guest_external_blind_stop, toSend);
        }
        if(currentLine.endsWith(F("GET /guest_external_blind_up"))) {
          sendSignal(guest_external_stop_moving_time, guest_external_blind_up, guest_external_blind_stop, toSend);
        }

        if(currentLine.endsWith(F("GET /master_internal_blind_down"))) {
          sendSignal(master_internal_stop_moving_time, master_internal_blind_down, master_internal_blind_stop, toSend);
        }
        if(currentLine.endsWith(F("GET /master_internal_blind_up"))) {
          sendSignal(master_internal_stop_moving_time, master_internal_blind_up, master_internal_blind_stop, toSend);
        }

        if(currentLine.endsWith(F("GET /master_external_blind_down"))) {
          sendSignal(master_external_stop_moving_time, master_external_blind_down, master_external_blind_stop, toSend);
        }
        if(currentLine.endsWith(F("GET /master_external_blind_up"))) {
          sendSignal(master_external_stop_moving_time, master_external_blind_up, master_external_blind_stop, toSend);
        }
      }
    }

    client.stop();
    delay(1);

    Serial.println(F("-- client disconnected --"));

    if(toSend != nullptr) {
      sendCommand(toSend);
    }
  }
}