#include "FastLED.h"

//number of LEDS on string
#define NUM_LEDS 360

// assign dataport to each string
#define DATA_PIN 10
#define DATA_PIN1 11
#define DATA_PIN2 12

// Define the array of leds
CRGB leds[NUM_LEDS];

char data;
static uint8_t hue;

void setup() { 
    Serial.begin(9600);
//	Serial.println("resetting");
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(120);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(0, INPUT);
    digitalWrite(DATA_PIN, HIGH);
 if (Serial.available() > 0)
	{
	data = Serial.read();
	Serial.print (data);
	Serial.print ("\n");
	if (data == '1')
	digitalWrite(DATA_PIN, LOW);
	}
}
void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }             

void loop() { 

 if (data == '1') 
 {//run lightshow
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
}
