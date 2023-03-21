#include "Adafruit_TCS34725.h"
#include <Wire.h>

#include "TCA9548.h"
#define offset 52
TCA9548 MP_0(0x70);
TCA9548 MP_1(0x71);

Adafruit_TCS34725 tcs0 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs4 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs5 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs6 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs7 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs8 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// all the info associated with each colour sensor

typedef struct{
  Adafruit_TCS34725 tcs;
  int8_t chan;
  int8_t mux;
  int8_t rgb;
}COLOUR_SENSOR;

// the pins the RGB's are connected to
typedef struct{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB;

// The digital pins the anodes are connected to
typedef struct{
    uint8_t an0;
    uint8_t an1;
    uint8_t an2;  
} ANODES;

// the values associated with each RGB
typedef struct{
    float r;
    float g;
    float b;    
} RGB_VALUES;


COLOUR_SENSOR colour_sensor[]{
  /** tcs; chan; mux; rgb;**/
  {tcs0, 1, 0},
  {tcs1, 2, 0},
  {tcs2, 3, 0},
  {tcs3, 4, 0},
  {tcs4, 2, 1},
  {tcs5, 1, 1}
  
};


RGB_VALUES values[]{
  {0,100,0},// 00
  {0,100,0},//10
  {0,100,0},//20
  {0,100,0},//01
  {0,100,0},//11
  {0,100,0},//21
  {0,100,0},//02
  {0,100,0},//12
  {0,100,0} //22
};

RGB rgb[]{
  {2, 3, 4},
  {5, 6, 7},
  {8, 9, 10}
};

ANODES an[]{
  {23, 26, 29},
  {24, 27, 30},
  {25, 28, 31} };

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
  for (i = 0; i < 3; i++){
    pinMode(rgb[i].R, OUTPUT);
    pinMode(rgb[i].G, OUTPUT);
    pinMode(rgb[i].B, OUTPUT);
    pinMode(an[i].an0, OUTPUT);
    pinMode(an[i].an1, OUTPUT);
    pinMode(an[i].an2, OUTPUT);
    
    digitalWrite(an[i].an0, HIGH);
    digitalWrite(an[i].an1, HIGH);
    digitalWrite(an[i].an2, HIGH);
  }
  delay(100);



 }

/*
 * void get_colour()
 * this method allows us to retrieve a colour from a designated adafruit TCS34725 colour sensor
 * For our case, we had to use I2C mux's since we had many of these devices.
 */
void get_colour() {
    uint8_t i; 
    uint8_t j; 
    uint8_t m; 

    for(i = 0; i<6; i++){
      
      
      //sets RGB colour
      set_colour();
      // disables all the channels in both of the I2C MUX's.
      MP_1.disableAllChannels(); 
      set_colour();
      MP_0.disableAllChannels();
      set_colour();
      Serial.println(" TEST ");
  
      // Enables the wanted I2C MUX
      if (colour_sensor[i].mux)     MP_0.selectChannel(chan);
      else                          MP_1.selectChannel(chan);
      set_colour();
  
  
    // retrieves the colours from the sensor and sets to values struct
    colour_sensor[i].tcs.getRGB(&values[i].r, &values[i].g, &values[i].b);
    set_colour();
  
    Serial.print("R:\t"); Serial.print(int(red)); 
    Serial.print("\tG:\t"); Serial.print(int(green)); 
    Serial.print("\tB:\t"); Serial.print(int(blue));
    Serial.print("\n");
  }
  // disables all channels of both MUX's
  MP_1.disableAllChannels();
  set_colour();
  MP_0.disableAllChannels();
  set_colour();
}

/**
 * void set_colour()
 * author: Alex Bundgard 101189931
 * sets the colour of each of the RGBs using charlie plexing, fast enough to fool eyes
 * 
 * Charlieplexing allows us to use many less PWM pins to adderess many RGB's
 * In my case we wired 3 rows of RGB's. This code toggles one RGB from each row at a time by writing 0
 * to the anode of the wanted addresed RGB. Since it is a diode, having a high signal on the output 
 * disables the LED's of the RGBs we dont want to address. 
 * notes:
 * sets the output analog pins before writing 0 to the wanted anodes, else the previous colour
 * bleeds into the new one sicne it is refreshing so fast
 */
void set_colour(){
  // loop variables
    uint8_t i; // index of anodes
    uint8_t j; // not used as index, just condition
    uint8_t m; // index for rdg values and output analog pins

  // i is loop for index of the anodes  
  for (i = 0; i<3; i++){
    //Serial.print("i: "); Serial.print(i); Serial.print(" "); // for debugging
    //Serial.print("an[i]: "); Serial.print(an[i].an0); Serial.print(" "); Serial.print(an[i].an1); Serial.print(" "); Serial.print(an[i].an2); Serial.print(" "); // for debuging
    for (m = 0; m < 3; m++){
      //Serial.print("\n ");
        for(j = 0; j < 3; j++){
          // it is m+i*3 because the pins are set up for the values 
          // in terms of the different rows, i.e. goes first element of row 0, then first element of row 1, then first of row 2, the second of row 0...
          // so to index it, you have the iteration variable m, plus the current row you are on
        analogWrite(rgb[m].R, values[m+i*3].r);
        analogWrite(rgb[m].G, values[m+i*3].g);
        analogWrite(rgb[m].B, values[m+i*3].b);
        
        //dubugging things
        //Serial.print("m: "); Serial.print(m); Serial.print(" ");
        //Serial.print("rgb[m]: "); Serial.print(rgb[m].R); Serial.print(" "); Serial.print(rgb[m].G); Serial.print(" "); Serial.print(rgb[m].B); Serial.print(" ");
        //Serial.print("j: "); Serial.print(j); Serial.print(" ");
        //Serial.print("values[m+i*3] : "); Serial.print(values[m+i*3].r); Serial.print(" "); Serial.print(values[m+i*3].g); Serial.print(" "); Serial.print(values[m+i*3].b); Serial.print("\n ");

        }
    }
//delay(5);
    // writes 0 to the i'th element of each row in the RGB layout, allows us to address that pin
    digitalWrite(an[i].an0, LOW);
    digitalWrite(an[i].an1, LOW);
    digitalWrite(an[i].an2, LOW);
    delay(3);
   //delay(1000); // toggle to see the colour slowly switching on the RGB's for debuging

    // writes 1 to the i'th element in RGB layout. Writing 1 turns off the RGB
    digitalWrite(an[i].an0, HIGH);
    digitalWrite(an[i].an1, HIGH);
    digitalWrite(an[i].an2, HIGH);
  }
}


void loop() {
  // Currently the loop function is used to test our code for this file.
  Serial.println("\nSECTION 2");
  

}
