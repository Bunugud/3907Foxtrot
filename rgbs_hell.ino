/**
#define R1 33
#define R2 23
#define R3 25
#define R4 27
#define R5 29
#define R6 31
#define G1 39
#define G2 41
#define G3 43
#define G4 45
#define G5 47
#define G6 49
#define B1 32
#define B2 22
#define B3 24
#define B4 26
#define B5 28
#define B6 30
**/

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
  uint8_t i;
  for( i = 0; i < sizeof(R)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
     digitalWrite(R[i].pinNum, HIGH);
  }
  delay(1000);
   for( i = 0; i < sizeof(R)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
     digitalWrite(R[i].pinNum, LOW);
  }

  for( i = 0; i < sizeof(G)/sizeof(pinInit_t); ++i ){
     pinMode(G[i].pinNum, OUTPUT);
     digitalWrite(G[i].pinNum, HIGH);
  }
  delay(1000);
  for( i = 0; i < sizeof(G)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
     digitalWrite(G[i].pinNum, LOW);
  }
  for( i = 0; i < sizeof(B)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
     digitalWrite(B[i].pinNum, HIGH);
  }
  delay(1000);
  for( i = 0; i < sizeof(B)/sizeof(pinInit_t); ++i ){
     pinMode(R[i].pinNum, OUTPUT);
     digitalWrite(B[i].pinNum, LOW);
  }

  delay(1000);
}

void loop() {
  
  uint8_t i;
  for( i = 0; i < sizeof(B)/sizeof(pinInit_t); ++i ){
    R[i].pinVal = 0;
    G[i].pinVal = 50;
    B[i].pinVal = 204;
    analogWrite(R[i].pinNum, R[i].pinVal);
    analogWrite(G[i].pinNum, G[i].pinVal);
    analogWrite(B[i].pinNum, B[i].pinVal);
    delay(1000);
  }

}
