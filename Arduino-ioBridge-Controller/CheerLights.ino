/*

 CheerLights!
 
 ioBridge API --> ioBridge IO-204 --> Arduino --> GE Color Effect Lights
 
 This sketch recieves serial commands from the Internet via the ioBridge API
 and relays them to a strand of GE Color Effects Lights. You can control the color
 of the lights be sending a serial string to the Arduino. Instead of using the
 ioBridge IO-204 module, you could also use ioBridge ZigBee, ioBridge iota,
 Arduino Ethernet, Ethernet Shield, or Arduino WiFi.
 
 Arduino Requirements:
 
   * Arduino
   * Arduino 1.0 IDE
   * GEColorEffects Arduino 1.0 Library
     http://www.digitalmisery.com/wp-content/uploads/2011/11/GEColorEffects-Arduino-1.0.zip
   
 Network Requirements:

   * Ethernet port on Router    
   * DHCP enabled on Router
 
 Created: Novemeber 29, 2011 by Hans Scharler - http://www.iamshadowlord.com
 
 Additional Credits:
 http://www.digitalmisery.com
 http://www.deepdarc.com
 
 To join the CheerLights project, visit http://www.cheerlights.com
 
*/

#include <GEColorEffects.h>

#define outPin 5        // Arduino pin # that's connected to the signal line on the GE Lights
#define lightCount 36   // Total # of lights on string (usually 50, 48, or 36)

static uint16_t c;

GEColorEffects lights(outPin, lightCount);  // Constructor

void setup() {
  lights.enumerate();  // Enumerate lights on string to enable individual bulb addressing
  delay(100);
  
  // Setup Serial
  Serial.begin(9600);
  delay(100);
  
  Serial.flush();
  delay(100);
}

void loop() {
  
  // Listen to serial commands from ioBridge
  if(Serial.available() > 0)
  {  
    delay(100); 

    char charIn = 0; 
    byte i = 0; 
    char stringIn[32] = "";
   
    while(Serial.available())
    {
      charIn = Serial.read();
      stringIn[i] = charIn; 
      i += 1;
    }
    
    // Echo Received Commands on the Serial Monitor
    Serial.println("CheerLight Command Received: "+String(stringIn));
    delay(200); 
    
    // Send matching commands to the GE-35 Color Effect Lights
    if (String(stringIn) == "white")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_WHITE);
    }
    else if (String(stringIn) == "black")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLACK);
    }
    else if (String(stringIn) == "red")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_RED);
    }
    else if (String(stringIn) == "green")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_GREEN);
    }
    else if (String(stringIn) == "blue")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLUE);
    }
    else if (String(stringIn) == "cyan")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_CYAN);
    }
    else if (String(stringIn) == "magenta")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_MAGENTA);
    }
    else if (String(stringIn) == "yellow")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_YELLOW);
    }
    else if (String(stringIn) == "purple")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_PURPLE);
    }
    else if (String(stringIn) == "orange")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_ORANGE);
    }
    else if (String(stringIn) == "warmwhite")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_WARMWHITE);
    }
    else if (String(stringIn) == "off")
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLACK);
    }
  }
} // End loop



