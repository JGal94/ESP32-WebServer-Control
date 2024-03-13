#include <WiFi.h>
#include <WebServer.h>
// Replace with your network credentials
const char* ssid = "FAMILIA AGALLON";
const char* password = "Cinturon2019";

const char* userweb = "admin";
const char* passweb = "admin";

IPAddress local_IP(192, 168, 100, 200);
// Set your Gateway IP address
IPAddress gateway(192, 168, 100, 1);

IPAddress subnet(255, 255, 255, 0);

// Set web server port number to 80
WebServer server(80);

// Variable to store the HTTP request


// Auxiliar variables to store the current output state
String out1s = "off";


// Assign output variables to GPIO pins
const int out1 = 2;


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 10000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(out1, OUTPUT);

  // Set outputs to LOW
  digitalWrite(out1, LOW);

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    if (!server.authenticate(userweb, passweb)) {
      return server.requestAuthentication();
    }
    server.handleClient();
  });
  server.begin();

}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }


  server.handleClient();


  

  //Serial.println("Client disconnected.");
 // Serial.println("");
  delay(20);
}


void handleClient() {
  String html = "";
}