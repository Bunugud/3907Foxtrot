#include "Adafruit_TCS34725.h"
#include <Wire.h>

#include "TCA9548.h"
#define offset 52
TCA9548 MP_0(0x70);
TCA9548 MP_1(0x71);

Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs4 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs5 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs6 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs7 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs8 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs9 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


typedef struct {
    uint8_t pinNum;
    int pinVal;
} pinInit_t;


pinInit_t B[] {
  {13, 0},
  {12, 0},
  {11, 0},
  {10, 0},
  {9, 0},
  {8, 0}
};

pinInit_t G[] {
  {7, 0},
  {6, 0},
  {5, 0},
  {4, 0},
  {3, 0},
  {2, 0}
};

pinInit_t R[] {
  {A8, 0},
  {A9, 0},
  {A10, 0},
  {A11, 0},
  {A12, 0},
  {A13, 0}
};


void setup() {
  
  // put your setup code here, to run once:
  pinMode(offset, OUTPUT);
  digitalWrite(offset, HIGH);
  Serial.begin(9600);

Wire.begin();
  if (MP_0.begin() == false)
  {
    Serial.println(" MP_0 COULD NOT CONNECT");
  }
  else
  {
    Serial.println(" MP_0 CONNECT");
  }

  if (MP_1.begin() == false)
  {
    Serial.println(" MP_1 COULD NOT CONNECT");
  }
  else
  {
    Serial.println(" MP_1 CONNECT");
  }

Serial.print("MP_0 \n");
for (int chan = 0; chan < 8; chan++)
  {

    Serial.print(chan); Serial.print(" ");
    Serial.print(MP_0.isEnabled(chan));
    MP_0.selectChannel(chan);
    Serial.print("\t");
    Serial.println(MP_0.isEnabled(chan));
    delay(100);
    MP_0.disableAllChannels();

  }

Serial.print("MP_1 \n");
for (int chan = 0; chan < 8; chan++)
  {

    Serial.print(chan); Serial.print(" ");
    Serial.print(MP_1.isEnabled(chan));
    MP_1.selectChannel(chan);
    Serial.print("\t");
    Serial.println(MP_1.isEnabled(chan));
    delay(100);
    MP_1.disableAllChannels();
  }


for (int chan = 0; chan < 8; chan ++){
      Serial.println(MP_0.isEnabled(chan));
      Serial.println(MP_1.isEnabled(chan)); 
      }

    MP_1.disableAllChannels();
    MP_0.disableAllChannels();
    delay(500);
        Serial.println(" TEST ");
    MP_0.selectChannel(1);
    delay(500);
//Serial.print(MP_0.isEnabled(1));


  uint8_t i;
  for( i = 0; i < sizeof(R)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
  }
  delay(1000);
   for( i = 0; i < sizeof(R)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
  }

  for( i = 0; i < sizeof(G)/sizeof(pinInit_t); ++i ){
     pinMode(G[i].pinNum, OUTPUT);
  }
  delay(1000);
  for( i = 0; i < sizeof(G)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
  }
  for( i = 0; i < sizeof(B)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
  }
  delay(1000);
  for( i = 0; i < sizeof(B)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
  }

  delay(100);



 }

void get_colour(Adafruit_TCS34725 tcs, int8_t chan, int8_t mux, int8_t rgb) {

    MP_1.disableAllChannels();
    MP_0.disableAllChannels();
    delay(500);
    Serial.println(" TEST ");

    if (!mux)     MP_0.selectChannel(chan);
    else     MP_1.selectChannel(chan);
    delay(500);

 if (tcs.begin()) {
    Serial.print("Found sensor"); Serial.print("\n");
 }
 else {Serial.print("No Sensor"); Serial.print("\n");}

  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);
  delay(200);

  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));
  Serial.print("\n");
  MP_1.disableAllChannels();
  MP_0.disableAllChannels();

  analogWrite(R[rgb].pinNum, red);
  analogWrite(G[rgb].pinNum, green);
  analogWrite(B[rgb].pinNum, blue);


  
}


void loop() {
  Serial.println("\nSECTION 2");
  
  Serial.println("\n 0, 1");
  get_colour(tcs1,1, 0, 0);

  delay(1000);

    Serial.println("\n 0, 2");
  get_colour(tcs2, 2, 0, 1);

  delay(1000);

    Serial.println("\n 0, 3");
  get_colour(tcs3, 3, 0, 2);

  delay(1000);

    Serial.println("\n 0, 4");
  get_colour(tcs4, 4, 0, 3);

  delay(1000);
  Serial.println("\n 1, 1");
  get_colour(tcs5, 2, 1, 4);

  delay(1000);
  
    Serial.println("\n 1, 2");
  get_colour(tcs6, 1, 1, 5);

  delay(1000);

  
}
