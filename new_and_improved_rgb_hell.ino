typedef struct{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} RGB;

typedef struct{
    uint8_t an0;
    uint8_t an1;
    uint8_t an2;  
} ANODES;

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;    
} RGB_VALUES;

RGB_VALUES values[]{
  {204,0,204}, //00
  {204,0,204}, //10
  {204,0,204}, //20
  {0,255,255}, //01
  {0,255,255},//11
  {0,255,255},//21
  {255,128,0}, //02
  {255,128,0}, // 12
  {255,128,0} //22
};

RGB rgb[]{
  {2, 3, 4},
  {5, 6, 7},
  {8, 9, 10}
};

ANODES an[]{
  {A5, A2, 11},
  {A4, A1, 12},
  {A3, A0, 13} };




void setup() {
    Serial.begin(9600);

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

/**
 * void loop()
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
 
void loop() {
    uint8_t i;
    uint8_t j;
    
    uint8_t m;


  for (i = 0; i<3; i++){

    //Serial.print("i: "); Serial.print(i); Serial.print(" ");
    //Serial.print("an[i]: "); Serial.print(an[i].an0); Serial.print(" "); Serial.print(an[i].an1); Serial.print(" "); Serial.print(an[i].an2); Serial.print(" ");
    for (m = 0; m < 3; m++){
      //Serial.print("\n ");

        for(j = 0; j < 3; j++){
        analogWrite(rgb[m].R, values[m+i*3].r);
        analogWrite(rgb[m].G, values[m+i*3].g);
        analogWrite(rgb[m].B, values[m+i*3].b);


        //Serial.print("m: "); Serial.print(m); Serial.print(" ");
        //Serial.print("rgb[m]: "); Serial.print(rgb[m].R); Serial.print(" "); Serial.print(rgb[m].G); Serial.print(" "); Serial.print(rgb[m].B); Serial.print(" ");
        //Serial.print("j: "); Serial.print(j); Serial.print(" ");
        //Serial.print("values[m+i*3] : "); Serial.print(values[m+i*3].r); Serial.print(" "); Serial.print(values[m+i*3].g); Serial.print(" "); Serial.print(values[m+i*3].b); Serial.print("\n ");
        }
    }
//delay(5);

    digitalWrite(an[i].an0, LOW);
    digitalWrite(an[i].an1, LOW);
    digitalWrite(an[i].an2, LOW);
    delay(3);
   //delay(1000);
    
    digitalWrite(an[i].an0, HIGH);
    digitalWrite(an[i].an1, HIGH);
    digitalWrite(an[i].an2, HIGH);
  }
  
}
