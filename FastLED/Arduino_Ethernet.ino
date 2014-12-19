/*

 CheerLights!
 
 CheerLights Channel --> Arduino Ethernet --> FastLED
 
 This sketch subscribes to the CheerLights ThingSpeak Channel and relays the
 last color from the Internet to a FastLED compatible RGB Light like Neopixels
 or RGB-123 light panels. This sketch uses DHCP to obtain an IP address
 automatically and requires Arduino 1.0+.
 
 Arduino Requirements:
 
 * Arduino Ethernet (or Arduino + Ethernet Shield)
 * Arduino 1.0+ IDE
 * FastLED Library - https://github.com/FastLED/FastLED/releases
 
 Network Requirements:
 * Ethernet port on Router
 * DHCP enabled on Router
 * Unique MAC Address for Arduino
 
 Created: December 19, 2014 by Hans Scharler - http://nothans.com
 
 Additional Credits:
 Example sketches from FastLED
 
 ThingSpeak Tutorial:
 http://community.thingspeak.com/tutorials/arduino/cheerlights-with-arduino-and-the-fastled-library/
 
 To join the CheerLights project, visit http://www.cheerlights.com
 
*/

#include <SPI.h>
#include <Ethernet.h>
#include "FastLED.h"

// Define the number of LED in strip or on panel
#define NUM_LEDS 8

// For LED chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For LED chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 6
#define CLOCK_PIN 13

// Define the array of LEDs
CRGB leds[NUM_LEDS];

// Local Network Settings
byte mac[] = {
  0xD4, 0x28, 0xB2, 0xFF, 0xA0, 0xA1 }; // Must be unique on local network

// ThingSpeak / CheerLights Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String thingSpeakChannel = "1417";                // Channel number of the CheerLights Channel
String thingSpeakField = "1";                     // Field number of the CheerLights Colors
const int thingSpeakInterval = 10 * 1000;         // Time interval in milliseconds to get data from ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0;
String lastCommand = "";
boolean lastConnected = false;
int failedCounter = 0;

// Initialize Arduino Ethernet Client
EthernetClient client;

void setup() {
  // Setup Serial
  Serial.begin(9600);
  delay(100);

  Serial.flush();
  delay(100);

  // Start Ethernet on Arduino
  startEthernet();

  // Setup FastLED
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
}

void loop() {

  // Process CheerLights Commands
  if(client.available() > 0)
  {  
    delay(100);

    String response;
    char charIn;

    do {
      charIn = client.read(); // read a char from the buffer
      response += charIn; // append that char to the string response
    }
    while (client.available() > 0);
       
    // Send matching commands to LEDs
    if (response == "white")
    {
      lastCommand = "white";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "red")
    {
      lastCommand = "red";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "green")
    {  
      lastCommand = "green";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "blue")
    {  
      lastCommand = "blue";  

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "cyan")
    {  
      lastCommand = "cyan";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Cyan;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "magenta")
    {  
      lastCommand = "magenta";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Magenta;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "yellow")
    {  
      lastCommand = "yellow";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Yellow;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "purple")
    {  
      lastCommand = "purple";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Purple;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "orange")
    {  
      lastCommand = "orange";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Orange;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "warmwhite")
    {  
      lastCommand = "warmwhite";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::OldLace;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "oldlace")
    {  
      lastCommand = "oldlace";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::OldLace;
        FastLED.show();
        delay(30);
      }
    }
    else if (response == "pink")
    {  
      lastCommand = "pink";

      for(int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Pink;
        FastLED.show();
        delay(30);
      }
    }
    else
    {
      lastCommand = "(no match)";
    }

    // Echo command
    delay(200);
    Serial.println("CheerLight Command Received: "+lastCommand);
    Serial.println();
    delay(200);
  }

  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();

    client.stop();
  }

  // Subscribe to ThingSpeak Channel and Field
  if(!client.connected() && (millis() - lastConnectionTime > thingSpeakInterval))
  {
    subscribeToThingSpeak(thingSpeakChannel, thingSpeakField);
  }

  // Check if Arduino Ethernet needs to be restarted
  if (failedCounter > 3) {
    startEthernet();
  }

  lastConnected = client.connected();

} // End loop

void subscribeToThingSpeak(String tsChannel, String tsField)
{
  if (client.connect(thingSpeakAddress, 80))
  {         
    Serial.println("Connecting to ThingSpeak...");
    Serial.println();

    failedCounter = 0;

    client.println("GET /channels/"+tsChannel+"/field/"+tsField+"/last.txt");
    client.println();

    lastConnectionTime = millis();
  }
  else
  {
    failedCounter++;

    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");
    Serial.println();

    lastConnectionTime = millis();
  }
}

void startEthernet()
{

  client.stop();

  Serial.println("Connecting Arduino to network...");
  Serial.println();

  delay(1000);

  // Connect to network amd obtain an IP address using DHCP
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP Failed, reset Arduino to try again");
    Serial.println();
  }
  else
  {
    Serial.println("Arduino connected to network using DHCP");
    Serial.println();
  }

  delay(1000);
}
