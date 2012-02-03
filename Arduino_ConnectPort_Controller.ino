/*

 CheerLights!
 
 CheerLights Channel --> ConnectPort X2 --> XBee --> Arduino --> GE Color Effect Lights
 
 This sketch subscribes to the CheerLights ThingSpeak Channel and relays the
 last command from the Internet to a strand of GE Color Effects Lights via the Digi
 ConnectPort X2.
 
 Arduino Requirements:
 
   * Arduino base board
   * XBee Shield (or breadboardable XBee)
   * Arduino 1.0 IDE
   * GEColorEffects Arduino 1.0 Library
     http://www.digitalmisery.com/wp-content/uploads/2011/11/GEColorEffects-Arduino-1.0.zip
   
 Addiontal Requirements:

   * Ethernet port on Router    
   * DHCP enabled on Router
   * ConnectPort X2 with XIG
   * XBee Series 2 Radios (x2)
   
 Created: Novemeber 29, 2011 by Hans Scharler - http://www.iamshadowlord.com
 
 Additional Credits:
   * http://www.digitalmisery.com
   * http://www.deepdarc.com
   * Networked On Air Light by Matt Richardson
 
 To join the CheerLights project, visit http://www.cheerlights.com
 
*/

#include <GEColorEffects.h>

// Color Effects Setup
#define outPin 5        // Arduino pin # that's connected to the signal line on the GE Lights
#define lightCount 36   // Total # of lights on string (usually 50, 48, or 36)

static uint16_t c;

GEColorEffects lights(outPin, lightCount);

void setup() {
  lights.enumerate();  // Enumerate lights on string to enable individual bulb addressing
  delay(100);
  
  // Setup Serial
  Serial.begin(115200);
  delay(1000);
  
  Serial.flush();
  delay(1000);
}

void loop() {
    
  Serial.println("http://api.thingspeak.com/channels/1417/field/1/last.txt");
  delay(3000);
  
  // Process CheerLights Commands
  if(Serial.available() > 0)
  {  
    delay(100); 
    
    String response;
    char charIn;

    do {
        charIn = Serial.read(); // read a char from the buffer
        response += charIn; // append that char to the string response
      } while (Serial.available() > 0); 
          
    // Send matching commands to the GE-35 Color Effect Lights
    if (response.indexOf("white") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_WHITE);
    }
    else if (response.indexOf("black") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLACK);
    }
    else if (response.indexOf("red") > 0)
    {    
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_RED);
    }
    else if (response.indexOf("green") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_GREEN);
    }
    else if (response.indexOf("blue") > 0)
    {   
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLUE);
    }
    else if (response.indexOf("cyan") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_CYAN);
    }
    else if (response.indexOf("magenta") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_MAGENTA);
    }
    else if (response.indexOf("yellow") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_YELLOW);
    }
    else if (response.indexOf("purple") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_PURPLE);
    }
    else if (response.indexOf("orange") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_ORANGE);
    }
    else if (response.indexOf("warmwhite") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_WARMWHITE);
    }
    else if (response.indexOf("black") > 0)
    {  
        lights.fill_color(0, lightCount, DEFAULT_INTENSITY, COLOR_BLACK);
    }
    
    delay(1000); 
    Serial.flush();
   
  }
  
  delay(10000); 
  
} // End loop


