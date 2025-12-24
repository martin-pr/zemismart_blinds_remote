constexpr char ssid[] = "There's no place like home";
constexpr char pass[] = "<password>";

#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

void setLedColor(unsigned char red, unsigned char green, unsigned char blue) {
  WiFiDrv::analogWrite(RED_LED, red);
  WiFiDrv::analogWrite(GREEN_LED, green);
  WiFiDrv::analogWrite(BLUE_LED, blue);
}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void printWebPageContent(WiFiClient& client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  client.println("<html>");
  client.println("<body>");
  client.println("LED control:");
  client.println("<li><a href=\"/R\">red</a>");
  client.println("<li><a href=\"/G\">green</a>");
  client.println("<li><a href=\"/B\">blue</a>");
  client.println("<li><a href=\"/W\">white</a>");
  client.println("</body>");
  client.println("</html>");

  client.println();
}

/////////////////////////////////////////////

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  WiFiDrv::pinMode(RED_LED, OUTPUT);
  WiFiDrv::pinMode(GREEN_LED, OUTPUT);
  WiFiDrv::pinMode(BLUE_LED, OUTPUT);

  Serial.begin(9600);

  setLedColor(10, 0, 0);
  Serial.println("Starting wifi...");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    setLedColor(255, 0, 0);
    while (true);       // don't continue
  }  

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
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

  setLedColor(0, 10, 0);
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("-- new client --");
    String currentLine = "";
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

        // Check to see if the client request was "GET /X"
        if (currentLine.endsWith("GET /R")) {
          setLedColor(255, 0, 0);
        }
        if (currentLine.endsWith("GET /G")) {
          setLedColor(0, 255, 0);
        }
        if (currentLine.endsWith("GET /B")) {
          setLedColor(0, 0, 255);
        }
        if (currentLine.endsWith("GET /W")) {
          setLedColor(255, 255, 255);
        }
      }
    }

    client.stop();
    Serial.println("-- client disconnected --");
  }
}