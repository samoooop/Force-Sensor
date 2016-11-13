/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 12

#define BRIGHTNESS 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String color="000000";

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}

void onStringComplete(void){
  int t_led_select = 0;
  static int led_select = -1;
  int R=0,G=0,B=0;
  if(inputString[0] == 'c'){
    R = charToHex(inputString[1])*16+charToHex(inputString[2]);
    G = charToHex(inputString[3])*16+charToHex(inputString[4]);
    B = charToHex(inputString[5])*16+charToHex(inputString[6]);
    Serial.println("setting color");
      setLedColor(R, G, B, led_select);
//    if(led_select == -1){
//      fullColor(R,G,B);
//    }else{
//      strip.setPixelColor(led_select, strip.Color(R,G,B) );
//      strip.show();
//    }
  }
  if(inputString[0] == 's'){
    if(inputString[1] == 'a'){
      led_select = -1;
      Serial.println("setting led : all");
    }
    else if(inputString[1] == 'c'){
      led_select = 0;
      Serial.println("setting led : none");
    }
    else{
      t_led_select = atoi(&inputString[1]);
      if(t_led_select <= 0 || t_led_select > strip.numPixels() )
        Serial.println("setting led : fail --> input must be 1-" + String(strip.numPixels()));
      else{
        led_select = led_select ^ 1<<(t_led_select - 1);
        Serial.println("setting led : " + String(led_select));
      }
    }
  }
  if(inputString[0] == 'b'){
    int brightness = 0;
    brightness = atoi(&inputString[1]);
    if(brightness < 0) brightness = 0;
    if(brightness > 100) brightness = 100;
    strip.setBrightness(brightness);
    strip.show();
    Serial.println("bobby is ku");
  }
  inputString = "";                                              // clear the string
}

void loop() {
  // main program loop
}

int charToHex(char c){
  if(c>='A' && c<='F')
    return c-'A'+10;
  if(c>='0' && c<='9')
    return c-'0';
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      onStringComplete();
    } 
  }
}


void fullColor(int R,int G,int B) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(R,G,B) );
    }
    strip.show();
}
void setLedColor(int R, int G, int B, int led_selector_flag){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      if(led_selector_flag & 1<<i)
        strip.setPixelColor(i, strip.Color(R,G,B) );
    }
    strip.show();
}
