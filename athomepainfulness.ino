#include <FastLED.h>
#include "Adafruit_TCS34725.h"
#include <Wire.h>
#include "TCA9548.h"

#define LED_PIN0    5
#define LED_PIN1    6
#define LED_PIN2    7

#define NUM_LEDS    2

#define BRIGHTNESS  30
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds0[NUM_LEDS];
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

TCA9548 MP_0(0x70);

Adafruit_TCS34725 tcs0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

typedef struct{
  Adafruit_TCS34725 tcs;
  int8_t mux;
  int8_t chan;
  CRGB leds[NUM_LEDS];
  float r;
  float g;
  float b;  
}LED_SENSOR_PAIRS;


LED_SENSOR_PAIRS info[]{
   {tcs0,0,6,leds0[NUM_LEDS],0,255,0},
   {tcs1,0,5,leds1[NUM_LEDS],0,255,0},  
   {tcs2,0,2,leds2[NUM_LEDS],0,255,0} 
};
void setup() {

   delay( 3000 ); // power-up safety delay
   FastLED.addLeds<LED_TYPE, LED_PIN0, COLOR_ORDER>(info[0].leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.addLeds<LED_TYPE, LED_PIN1, COLOR_ORDER>(info[1].leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(info[2].leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   FastLED.setBrightness(  BRIGHTNESS );
  
   Serial.begin(9600);
   delay(10);
  Wire.begin();
  if (MP_0.begin() == false)
  {
    Serial.println(" MP_0 COULD NOT CONNECT");
  }
  else
  {
    Serial.println(" MP_0 CONNECT");
  }


}

CRGB closest_colour(int8_t i){
  if(info[i].r > info[i].g  && info[i].r > info[i].b){
    return CRGB::Red;
  }
  else if(info[i].g > info[i].r  && info[i].g > info[i].b){
    return CRGB::Green;
  }
  else if(info[i].g > info[i].r  && info[i].g > info[i].b){
    return CRGB::DarkBlue;
  }
  else return CRGB::HotPink;
}

void get_colour(){
  uint8_t i;

  for (i = 0; i<3; i++){
    MP_0.disableAllChannels();
    delay(10);
    MP_0.selectChannel(info[i].chan);
    
    info[i].tcs.getRGB(&info[i].r, &info[i].g, &info[i].b);
      
    Serial.print("R:\t"); Serial.print(int(info[i].r)); 
    Serial.print("\tG:\t"); Serial.print(int(info[i].g)); 
    Serial.print("\tB:\t"); Serial.print(int(info[i].b    ));
    Serial.print("\n");
    delay(10);
    
    info[i].leds[0] = closest_colour(i);
    info[i].leds[1] = closest_colour(i);
    delay(10);
    FastLED.show();   

  }

}

void test_rgb(){
        uint8_t i;
        for (i = 0; i<3; i++){
        info[i].leds[0] = CRGB::Red ;
        info[i].leds[1] = CRGB::Red ;
            FastLED.show();
        delay(1000);    
        info[i].leds[0] = CRGB::Orange;
        info[i].leds[1] = CRGB::Orange;
            FastLED.show();
        delay(1000);    
        info[i].leds[0] = CRGB::Yellow;
        info[i].leds[1] = CRGB::Yellow;
            FastLED.show();
        delay(1000);    
        info[i].leds[0] = CRGB::Green;
        info[i].leds[1] = CRGB::Green;
            FastLED.show();
        delay(1000);
        info[i].leds[0] = CRGB::Aqua;
        info[i].leds[1] = CRGB::Aqua;
            FastLED.show();
        delay(1000);    
        info[i].leds[0] = CRGB::Blue;
        info[i].leds[1] = CRGB::Blue;
            FastLED.show();
        delay(1000);    
        info[i].leds[0] = CRGB::Purple;
        info[i].leds[1] = CRGB::Purple;
            FastLED.show();
        delay(1000);    
        info[i].leds[0] = CRGB::Pink;
        info[i].leds[1] = CRGB::Pink;
            FastLED.show();
        delay(1000); }
        }
  
  void loop() {
    //test_rgb();
    get_colour();
  }
   
