
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <M5Stack.h>

// Set these to your desired credentials.
const char *ssid = "ssid_Name";
const char *password = "password";
String request;

WiFiServer server(80);           //launches and sets webserver port

void setup() {
 
  M5.begin();
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  //Serial Display
  Serial.println("Server started");
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  //M5 LCD Display
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("AP IP address: ");
  M5.Lcd.println(myIP);
  
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("Client Connected");     // print a message out the serial port
    client.print("From Server");            // Send message to Client
    request = client.readStringUntil('\r'); // Reading message from client
    Serial.println(request);                // printing message from client

  }

}
