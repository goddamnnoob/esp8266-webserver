#include <ESP8266WiFi.h>

// network credentials
const char* ssid     = "SSID";
const char* password = "PASSWORD";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables
String bot1state = "off";
String bot1battery = "0";
String bot1oil = "0";
String bot2state = "off";
String bot2battery = "0";
String bot2oil = "0";
String bot3state = "off";
String bot3battery = "0";
String bot3oil = "0";
String bot4state = "off";
String bot4battery = "0";
String bot4oil = "0";
String output4State = "off";


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);


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
  //code to get the battery and oil values from the bots


  //web server
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
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
            if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("bot 1 start");
              bot1state = "on";
              // signal the bot 1 to start
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("bot 1 off");
              bot1state = "off";
              //signal bot 1 to come back
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("bot 2 start");
              bot2state = "on";
              // signal the bot 2 to start
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("bot 2 off");
              bot2state = "off";
              //signal bot 2 to come back
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("bot 3 start");
              bot3state = "on";
              // signal the bot 3 to start
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("bot 3 off");
              bot3state = "off";
              //signal bot 3 to come back
            }
              else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("bot 4 start");
              bot4state = "on";
              // signal the bot 4 to start
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("bot 4 off");
              bot4state = "off";
              //signal bot 4 to come back
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state,battery,oil
            client.println("<p>Bot 1 - State " + bot1state + "</p>");
            client.println("<p>Bot 1 - Battery " + bot1battery + "</p>");
            client.println("<p>Bot 1 - Oil " + bot1oil + "</p>");
            client.println("<p>Bot 2 - State " + bot2state + "</p>");
            client.println("<p>Bot 2 - Battery " + bot2battery + "</p>");
            client.println("<p>Bot 2 - Oil " + bot2oil + "</p>");
            client.println("<p>Bot 3 - State " + bot3state + "</p>");
            client.println("<p>Bot 3 - Battery " + bot3battery + "</p>");
            client.println("<p>Bot 3 - Oil " + bot3oil + "</p>");
            client.println("<p>Bot 4 - State " + bot4state + "</p>");
            client.println("<p>Bot 4 - Battery " + bot4battery + "</p>");
            client.println("<p>Bot 4 - Oil " + bot4oil + "</p>");
           
                
            if (bot1state=="off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button1on\">BOT1 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button1off\">BOT1 OFF</button></a></p>");
            } 
                        if (bot2state=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button2on\">BOT2 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button2off\">BOT2 OFF</button></a></p>");
            } 
                        if (bot3state=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button3on\">BOT3 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button3off\">BOT3 OFF</button></a></p>");
            } 
                        if (bot4state=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button4on\">BOT4 ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button4off\">BOT4 OFF</button></a></p>");
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
