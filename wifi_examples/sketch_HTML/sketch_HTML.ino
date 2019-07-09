/*
 * You can replace X and Y with desired pins
 */

// Load Wi-Fi library
#include <WiFi.h>
#include <M5Stack.h>


// Replace with your network credentials
const char* ssid     = "ssid";
const char* password = "password";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String outputState_X = "off";
String outputState_Y = "off";

// Assign output variables to pins
const int output_X = 26;
const int output_Y = 27;

void setup() {
  
  M5.begin();
  Serial.begin(115200);
  
  // Initialize the output variables as outputs
  pinMode(output_X, OUTPUT);
  pinMode(output_Y, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output_X, LOW);
  digitalWrite(output_Y, LOW);

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
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /X/on") >= 0) {
              Serial.println("GPIO X on");
              outputState_X = "on";
              digitalWrite(output_X, HIGH);
            } else if (header.indexOf("GET /X/off") >= 0) {
              Serial.println("GPIO X off");
              outputState_X = "off";
              digitalWrite(output_X, LOW);
            } else if (header.indexOf("GET /Y/on") >= 0) {
              Serial.println("GPIO Y on");
              outputState_Y = "on";
              digitalWrite(output_Y, HIGH);
            } else if (header.indexOf("GET /Y/off") >= 0) {
              Serial.println("GPIO Y off");
              outputState_Y = "off";
              digitalWrite(output_Y, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for X 
            client.println("<p>X - State " + outputState_X + "</p>");
            // If the outputState_X is off, it displays the ON button       
            if (outputState_X=="off") {
              client.println("<p><a href=\"/X/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/X/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for Y 
            client.println("<p>Y - State " + outputState_Y + "</p>");
            // If the outputState_Y is off, it displays the ON button       
            if (outputState_Y=="off") {
              client.println("<p><a href=\"/Y/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/Y/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
