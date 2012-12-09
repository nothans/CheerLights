/*

 CheerLights!
 
 CheerLights Channel --> Arduino Ethernet --> GE Color Effect Lights
 
 This sketch subscribes to the CheerLights ThingSpeak Channel and relays the
 last command from the Internet to a strand of GE Color Effects Lights. This
 sketch uses DHCP to obtain an IP address automatically and requires Arduino 1.0.
 
 Arduino Requirements:
 
   * Arduino Ethernet (or Arduino + Ethernet Shield)
   * Arduino 1.0 IDE
   * GEColorEffects Arduino 1.0 Library
     http://www.digitalmisery.com/wp-content/uploads/2011/11/GEColorEffects-Arduino-1.0.zip
   
 Network Requirements:

   * Ethernet port on Router    
   * DHCP enabled on Router
   * Unique MAC Address for Arduino

 Getting a Globally Unique MAC Address from ThingSpeak:
 
   * Sign Up for New User Account - https://www.thingspeak.com/users/new
   * Register your Arduino by selecting Devices, Add New Device
   * Once the Arduino is registered, click Generate Unique MAC Address
   * Enter the new MAC Address in this sketch under "Local Network Settings"
 
 Created: Novemeber 29, 2011 by Hans Scharler - http://www.iamshadowlord.com
 
 Additional Credits:
 http://www.digitalmisery.com
 http://www.deepdarc.com
 
 To join the CheerLights project, visit http://www.cheerlights.com
 
*/

#include <GEColorEffects.h>
#include <SPI.h>
#include <Ethernet.h>

// Color Effects Setup
#define outPin 5        // Arduino pin # that's connected to the signal line on the GE Lights
#define lightCount 36   // Total # of lights on string (usually 50, 48, or 36)

static uint16_t c;

GEColorEffects lights(outPin, lightCount);

// Local Network Settings
byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0xA0, 0xA1 }; // Must be unique on local network

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String thingSpeakChannel = "1417";                // Channel number of the CheerLights Channel
String thingSpeakField = "1";                     // Field number of the CheerLights commands 
const int thingSpeakInterval = 16 * 1000;      // Time interval in milliseconds to get data from ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0; 
String lastCommand = "";
boolean lastConnected = false;
int failedCounter = 0;

// Initialize Arduino Ethernet Client
EthernetClient client;

void setup() {
  lights.enumerate();  // Enumerate lights on string to enable individual bulb addressing
  delay(100);
  
  // Setup Serial
  Serial.begin(9600);
  delay(100);
  
  Serial.flush();
  delay(100);
  
  // Start Ethernet on Arduino
  startEthernet();
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
      } while (client.available() > 0); 
          
    // Send matching commands to the GE-35 Color Effect Lights
    if (response.indexOf("white") > 0)
    {  
        lastCommand = "white";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_WHITE);
    }
    else if (response.indexOf("black") > 0)
    {  
        lastCommand = "black";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLACK);
    }
    else if (response.indexOf("red") > 0)
    {  
        lastCommand = "red";   
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_RED);
    }
    else if (response.indexOf("green") > 0)
    {  
        lastCommand = "green";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_GREEN);
    }
    else if (response.indexOf("blue") > 0)
    {  
        lastCommand = "blue";  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLUE);
    }
    else if (response.indexOf("cyan") > 0)
    {  
        lastCommand = "cyan";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_CYAN);
    }
    else if (response.indexOf("magenta") > 0)
    {  
        lastCommand = "magenta";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_MAGENTA);
    }
    else if (response.indexOf("yellow") > 0)
    {  
        lastCommand = "yellow";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_YELLOW);
    }
    else if (response.indexOf("purple") > 0)
    {  
        lastCommand = "purple";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_PURPLE);
    }
    else if (response.indexOf("orange") > 0)
    {  
        lastCommand = "orange";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_ORANGE);
    }
    else if (response.indexOf("warmwhite") > 0)
    {  
        lastCommand = "warmwhite";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_WARMWHITE);
    }
    else if (response.indexOf("black") > 0)
    {  
        lastCommand = "black";
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLACK);
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
  if (failedCounter > 3 ) {startEthernet();}
  
  lastConnected = client.connected();
  
} // End loop

void subscribeToThingSpeak(String tsChannel, String tsField)
{
  if (client.connect(thingSpeakAddress, 80))
  {         
    Serial.println("Connecting to ThingSpeak...");
    Serial.println();
      
    failedCounter = 0;
    
    client.println("GET /channels/"+tsChannel+"/field/"+tsField+"/last.txt HTTP/1.0");
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




