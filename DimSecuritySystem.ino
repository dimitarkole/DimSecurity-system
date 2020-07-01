#include <LiquidCrystal.h> //include LCD library (standard library)
#include <Keypad.h> //include keypad library - first you must install library (library link in the video description)

#define yellowLED 10 //define the LED pins
#define greenLED 11
#define redLED 12
#define piezo 9

char* password ="1234"; //create a password
int position = 0; //keypad position
int countLetter = 0; 
bool startFlag=true;
const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;
int  countDoFailurePassword = 0;
int  countFailurePassword = 1;

char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins [rows] = {1, 2, 3, 4}; //pins of the keypad
byte colPins [cols] = {5, 6, 7, 8};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); // pins of the LCD. (RS, E, D4, D5, D6, D7)

void setup(){
  lcd.begin(16, 2);
  pinMode(yellowLED, OUTPUT);  //set the LED as an output
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(piezo, OUTPUT);

  setLocked (true); //state of the password
  
}

void loop(){

 char whichKey = myKeypad.getKey(); //define which key is pressed with getKey

 if(startFlag)
 {
   printWelcomeMessage();
   startFlag=false;
 }

 if(whichKey == '*' || whichKey == '#' || whichKey == 'A' ||       //define invalid keys
     whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){
  InvalidKey();
  }
  else if(whichKey!='\0'){
     lcd.setCursor(countLetter, 0);
     lcd.print(whichKey);
    countLetter++;
  }
  
  if(whichKey == password [position]){
    position ++;
  }
  if(position == strlen(password)){
    setLocked (false);
  }
  else if( countLetter == strlen(password)
          && position < strlen(password))
  {
      delay(500);

    lcd.clear();
    position=0;
    countLetter=0;
    countDoFailurePassword++;
  }
  delay(100);
  if(countDoFailurePassword==countFailurePassword)
  {
    IncorrectPassword();
  }
}

void setLocked(int locked){
  if(locked){
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
         digitalWrite(redLED, LOW);

    }
    else{
      digitalWrite(yellowLED, LOW);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("*** Verified ***");
      delay(3000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Mert Arduino");
      lcd.setCursor(0, 1);
      lcd.print("Tutorial Project");
      delay(7000);
      lcd.clear();
    }
}

void printWelcomeMessage(){
  lcd.setCursor(0, 0);
  lcd.print("    Welcome");
  lcd.setCursor(0, 1);
  lcd.print(" Enter Password");
  delay(1000);
  lcd.clear();
}

void IncorrectPassword(){
 digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("   Incorrect");
    lcd.setCursor(0, 1);
    lcd.print("    Password");
    tone(piezo, 400, 3000);
    delay(3000);
    countDoFailurePassword=0;
}

void InvalidKey(){
    position=0;
    setLocked (true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Invalid Key!");
    delay(1000);
    lcd.clear();
    printWelcomeMessage();
}