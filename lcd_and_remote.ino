// include the library code:
#include <LiquidCrystal.h>
#include "IRremote.h"


const int receiver = 5; // Signal Pin of IR receiver to Arduino Digital Pin 5
int curr_game_mode = 0;
const int num_games = 5;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output




/*-----( Function )-----*/

void choseMode(int op){
  curr_game_mode = curr_game_mode + op;
  
  switch(curr_game_mode){
  case 0: lcd.print("Welcome");
          break;
  case 1: lcd.print("Tik Tac Toe");
          break;
  case 2: lcd.print("Darts");
          break;
  default : lcd.print(curr_game_mode);
           break;
  }
  
}

/**
 * Starts specified game mode
 */
void start_game(){
  // do case statement that will figure out which game mode was chosen, 
  //then go to said games functions

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Starting in...");

  
  for (int i = 0; i<4; i++){
    lcd.setCursor(i+i*2,1);
    lcd.print(3-i);
    delay(1000);
  }
  lcd.setCursor(11,1);
  lcd.print("GO");
}



/** 
 *  Decodes the IR signal recieved. Performs the wanted operation
 */
void translateIR() // takes action based on IR code received

// describing Remote IR codes 
  
{

  switch(results.value)

  {
    /**
  case 0xFFA25D: Serial.println("POWER"); 
        lcd.print("POWER");
  break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); 
        lcd.print("FUNC/STO");
        break;
        
  case 0xFF629D: Serial.println("VOL+");
        lcd.print("VOL+");
         break;**/
  case 0xFF22DD: Serial.println("FAST BACK"); 
        lcd.print("FAST BACK");
         lcd.setCursor(0, 1);
         choseMode(-1);
           break;
  case 0xFF02FD: Serial.println("PAUSE");
        start_game(); 
            break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   
        lcd.print("FAST FORWARD");
         lcd.setCursor(0, 1);
         choseMode(1);
        break;
        /**
  case 0xFFE01F: Serial.println("DOWN");    
        lcd.print("DOWN");
        break;
  case 0xFFA857: Serial.println("VOL-");    
        lcd.print("VOL-");
        break;
  case 0xFF906F: Serial.println("UP");    
        lcd.print("UP");
        break;
  case 0xFF9867: Serial.println("EQ");    
        lcd.print("EQ");
        break;
  case 0xFFB04F: Serial.println("ST/REPT");    
        lcd.print("ST/REPT");
        break;
  case 0xFF6897: Serial.println("0");    
        lcd.print("0");
        break;
  case 0xFF30CF: Serial.println("1");    
        lcd.print("1");
        break;
  case 0xFF18E7: Serial.println("2");    
        lcd.print("2");
        break;
  case 0xFF7A85: Serial.println("3");    
        lcd.print("3");
        break;
  case 0xFF10EF: Serial.println("4");    
        lcd.print("4");
        break;
  case 0xFF38C7: Serial.println("5");    
        lcd.print("5");
        break;
  case 0xFF5AA5: Serial.println("6");    
        lcd.print("6");
        break;
  case 0xFF42BD: Serial.println("7");    
        lcd.print("7");
            break;
  case 0xFF4AB5: Serial.println("8");    
        lcd.print("8");
        break;
  case 0xFF52AD: Serial.println("9");    
        lcd.print("9");
        break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");    
        lcd.print("REPEAT");
        break;  **/

  default: 
    Serial.println(" ");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR



void setup() {
  
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("WELCOME");

  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);


}

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    lcd.clear();
    lcd.setCursor(0, 0);
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
  if (digitalRead(SW_pin) == LOW) {
 
    start_game();
  }
  else if(analogRead(X_pin) > 1000){
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("UP");
    lcd.setCursor(0, 1);
    choseMode(1);
    delay(1000);
  }
    else if(analogRead(X_pin) < 22){
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("DOWN");
    lcd.setCursor(0, 1);
    choseMode(-1);
    delay(1000);
  }
 
}/* --(end main loop )-- */
