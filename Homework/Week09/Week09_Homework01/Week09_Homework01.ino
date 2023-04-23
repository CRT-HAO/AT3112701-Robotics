#include <Arduino.h>
#include <WiFi.h>

#define LED_PIN 2

const char WIFI_SSID[] = "MI8";
const char WIFI_PASSWD[] = "0916819600";

WiFiServer server(80);

String header;

String ledState = "off";

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("... ");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            if (header.indexOf("GET /led/on") >= 0) {
              Serial.println("LED on");
              ledState = "on";
              digitalWrite(LED_PIN, true);
            } else if (header.indexOf("GET /led/off") >= 0) {
              Serial.println("LED off");
              ledState = "off";
              digitalWrite(LED_PIN, false);
            }else if (header.indexOf("GET /led/1") >= 0) {
              Serial.println("LED on");
              ledState = "on";
              digitalWrite(LED_PIN, true);
            } else if (header.indexOf("GET /led/0") >= 0) {
              Serial.println("LED off");
              ledState = "off";
              digitalWrite(LED_PIN, false);
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            client.println("<p>LED - State " + ledState + "</p>");
            if (ledState == "off") {
              client.println("<p><a href=\"/led/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/led/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            client.println("<div>");
            client.println("<span>Command</span>");
            client.println("<input type=\"text\" id=\"command\" value=\"1\">");
            client.println("<button onclick=\"submitCommand();\">Submit</button>");
            client.println("</div>");

            client.println("<script>function submitCommand() { window.location.href = \"../led/\" + String(document.getElementById(\"command\").value); }</script>");
               
            client.println("</body></html>");
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}