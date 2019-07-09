#include <WiFi.h>
#include <WiFiMulti.h>
#include <M5Stack.h>

WiFiMulti WiFiMulti;

// Use WiFiClient class to create TCP connections
WiFiClient client;

const uint16_t port = 80;         // defining port
const char *host = "192.168.4.1"; // ip or dns
String line;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    delay(10);

    //Connecting to a WiFi network
    WiFiMulti.addAP("Access_Point", "YxZ12000");

    Serial.println();
    Serial.println();
    Serial.print("Waiting for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);

    Serial.print("Connecting to ");
    Serial.println(host);
}


void loop()
{
    //If the client is not connected to the server
    if (!client.connect(host, port)) {
        Serial.println("Connection failed.");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000);
        return;
    }

    // This will send a request to the server
    client.print("Send this data to the server");
    
    //read back one line from the server
    line = client.readStringUntil('\r');
    Serial.println(line);
    
}
