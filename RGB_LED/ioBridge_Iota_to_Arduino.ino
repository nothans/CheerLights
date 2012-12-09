/*

 CheerLights!
 
 RealTime.io API --> ioBridge Iota --> Arduino --> RGB LED
 
 This sketch recieves serial commands from the Internet via the RealTime.io API
 and relays them to an RGB LED via an ioBridge Iota module. The ioBridge Iota sends
 the serial string to the Arduino, then the Arduino uses PWM to control the value of
 each color of an RGB LED.
 
 Parts:

   * RGB LED (common cathode)
   * ioBridge Iota
   * Arduino
   * 270 ohm resistor (x3)
   * Jumper wires
 
 Arduino Requirements:
 
   * Arduino 1.0 IDE
    
 Created: December 8, 2012 by Hans Scharler - http://www.iamshadowlord.com
  
 To join the CheerLights project, visit http://www.cheerlights.com
 
*/

#define GREEN 5
#define BLUE 3
#define RED 6

void setup() {
  
  // Setup Serial
  Serial.begin(9600);
  delay(100);
  
  Serial.flush();
  delay(100);
  
  // PWM Pin Setup
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
  
}

void loop() {
  
  // Listen to serial commands from the ioBridge Iota
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
    
    // Echo Received Commands on the Serial Monitor and RealTime.io Console
    Serial.print("CheerLights Command Received: "+String(stringIn));
    delay(200); 
    
    // Set colors by using PWM based on the incoming command
    if (String(stringIn) == "red")
    {  
        analogWrite( RED, 255 );
        analogWrite( GREEN, 0 );
        analogWrite( BLUE, 0);
    }
    else if (String(stringIn) == "green")
    {  
        analogWrite( RED, 0 );
        analogWrite( GREEN, 255 );
        analogWrite( BLUE, 0 );
    }
    else if (String(stringIn) == "blue")
    {  
        analogWrite( RED, 0 );
        analogWrite( GREEN, 0 );
        analogWrite( BLUE, 255 );
    }
    else if (String(stringIn) == "cyan")
    {
        analogWrite( RED, 0 );
        analogWrite( GREEN, 255 );
        analogWrite( BLUE, 255 );
    }
    else if (String(stringIn) == "purple")
    {  
        analogWrite( RED, 128 );
        analogWrite( GREEN, 0 );
        analogWrite( BLUE, 128 );
    }
    else if (String(stringIn) == "magenta")
    {
        analogWrite( RED, 255 );
        analogWrite( GREEN, 0 );
        analogWrite( BLUE, 255 );
    }
    else if (String(stringIn) == "yellow")
    {
        analogWrite( RED, 255 );
        analogWrite( GREEN, 255 );
        analogWrite( BLUE, 0 );
    }
    else if (String(stringIn) == "orange")
    {
        analogWrite( RED, 255 );
        analogWrite( GREEN, 165 );
        analogWrite( BLUE, 0 );
    }
    else if (String(stringIn) == "white" || String(stringIn) == "warmwhite")
    {  
        analogWrite( RED, 255 );
        analogWrite( GREEN, 255 );
        analogWrite( BLUE, 255 );
    }
    else if (String(stringIn) == "black" || String(stringIn) == "off")
    {
        analogWrite( BLUE, 0 );
        analogWrite( GREEN, 0 );
        analogWrite( RED, 0 );
    }
  }
  
} // End loop
