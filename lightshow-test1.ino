/*
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - Mayoogh Girish
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
//Edited and adapted to local project by wjh3

#define NUM_LEDS 360
#define DATA_PIN 10
CRGB leds[NUM_LEDS];	  //Define the array of leds
char data = 0;            //Variable for storing received data
static uint8_t hue;

void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(DATA_PIN, OUTPUT);  //Sets digital pin 13 as output pin
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(120);
}

void loop()
{
   if(Serial.available() > 0) {      // Send data only when you receive data:
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
 
	if(data == '1') {             // Checks whether value of data is equal to 1
		// run lightshow
        digitalWrite(DATA_PIN, HIGH); 		 
		hue = 0;
		Serial.print("x");
		// sets direction of led
		for(int i = 0; i < NUM_LEDS; i++) {
			// sets color
			leds[i] = CHSV(hue++, 255, 255);
			// Show the leds
			FastLED.show(); 
			// reset to black
			leds[i] = CRGB::Black;
			fadeall();
			// Wait and repeat
			delay(10);
		}
		Serial.print("x");

		// Now go in the other direction.  
		for(int i = (NUM_LEDS)-1; i >= 0; i--) {
			// sets color
			leds[i] = CHSV(hue++, 255, 255);
			// Show the leds
			FastLED.show();
			// reset to black
			// leds[i] = CRGB::Black;
			fadeall();
			// Wait and repeat
			delay(10);
		}
	}//end lightshow

	else(data == '0') {        //  Checks whether value of data is equal to 0
         digitalWrite(DATA_PIN, LOW);    //If value is 0 then DATA_PIN turns OFF
	}
	
   } //end if Serial available 
} // end loop
