#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x27, 16, 2);
int t=0;
int crypin = 2;
int eatpin = 3;
int buttonState = 0;
int clk = 20; 
int levelNum = 1;
int levelLim =4;
int dead = 0;
byte heart[] = 
{
  B00000,
  B11011,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
 };

byte left_reg[] =
 {
  B01111,
  B01000,
  B11010,
  B11000,
  B11000,
  B11011,
  B01000,
  B01111
 };


byte right_reg[] =
{
  B11110,
  B00010,
  B01011,
  B00011,
  B00011,
  B11010,
  B00010,
  B11110
 };

byte left_sad[] =
 {
  B01111,
  B01000,
  B11010,
  B11000,
  B11000,
  B11001,
  B01010,
  B01111
 };

byte right_sad[] =
 {
  B11110,
  B00010,
  B01011,
  B00011,
  B00011,
  B10010,
  B01010,
  B11110
 };

byte happy_left[] = 
{
  B01111,
  B01000,
  B11010,
  B11000,
  B11010,
  B11001,
  B01000,
  B01111
 };

byte happy_right[] =
 {
  B11110,
  B00010,
  B01011,
  B00011,
  B01011,
  B10010,
  B00010,
  B11110
 };


void setup()
 {
  pinMode(crypin, OUTPUT); \\bazzer
  pinMode(eatpin, INPUT); \\buton 
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, left_reg);
  lcd.home();
  lcd.setCursor(9,0);
  lcd.write(0);
  lcd.createChar(1, right_reg);
  lcd.home();
  lcd.setCursor(10,0);
  lcd.write(1);
  lcd.home();
  
 }

void loop() 
  { 
   
    for (int i = 0; i <= clk; i++)
    {
       if (dead==0) //check dead number
          {
           
            lcd.home(); 
            lcd.setCursor (8,1);
            lcd.write(2);
            lcd.createChar(2, heart);

            lcd.home(); 
            lcd.setCursor (9,1);
            lcd.write(2);
            lcd.createChar(2, heart);

            lcd.home(); 
            lcd.setCursor (10,1);
            lcd.write(2);
            lcd.createChar(2, heart);

          } 
           if (dead==1)
          {
          lcd.home(); 
            lcd.setCursor (8,1);
            lcd.write(2);
            lcd.createChar(2, heart);

            lcd.home(); 
            lcd.setCursor (9,1);
            lcd.write(2);
            lcd.createChar(2, heart);

            lcd.setCursor(10,1);
            lcd.print(" ");
          }
          if (dead==2)
          {
           lcd.home(); 
            lcd.setCursor (8,1);
            lcd.write(2);
            lcd.createChar(2, heart);

            lcd.setCursor(9,1);
            lcd.print(" ");

            lcd.setCursor(10,1);
            lcd.print(" ");
          }
          if (dead==3)
          {
            lcd.setCursor(0,0);
            lcd.print("GAME OVER");
          }
      digitalWrite(crypin , 0);  
      noTone(crypin);
      lcd.setCursor(13,1);
      lcd.print("  ");
      lcd.createChar(0, left_reg);
      lcd.home();
      lcd.setCursor(9,0);
      lcd.write(0);
      lcd.createChar(1, right_reg);
      lcd.setCursor(12,0);
      lcd.print("   ");
      lcd.setCursor(13,1);
      lcd.print("  ");
      lcd.setCursor(0,0);
      lcd.print("food ");
      lcd.setCursor(5,0);
      lcd.print("   ");
      lcd.setCursor(5,0);
      lcd.print(t);
      lcd.setCursor(0,1);
      lcd.print("level ");
      lcd.setCursor(6,1);
      lcd.print(levelNum);
      lcd.setCursor(13,0);
      lcd.print(i);
      delay (1000);                        //starting at level 1- clk  time defined (20s)
      if (i==clk)
        
        }       
    }
  }


int cry (t,level,levelNum,levelLim, dead,clk)
{
        i=0  ;
        for (int j = 0; j <= 30; j++)        //cloclk level 1 eat
         {
          if (j==30) 
          {
            t=t-1;
            dead=dead+1;
          }  
          lcd.setCursor(13,1);
          lcd.print(j);
          lcd.createChar(0, left_sad);
          lcd.home();
          lcd.setCursor(9,0);
          lcd.write(0);
          lcd.createChar(1, right_sad);
          lcd.home();
          lcd.setCursor(10,0);
          lcd.write(1);
          lcd.setCursor(12,0);
          lcd.print("cry ");
          digitalWrite(crypin , 1); 
          tone(crypin, 1000); // Send 1KHz sound signal
          delay(500);        
          noTone(crypin);     // Stop sound
          delay(500);         // total for 1 sec
          buttonState = digitalRead(eatpin);
          delay (100);
          if (buttonState == HIGH)
            {
              dead=0;
              noTone(crypin);
              lcd.setCursor(12,0);
              lcd.print("eat");
              t=t+1;
              lcd.setCursor(13,1);
              lcd.print("  ");
              lcd.createChar(0, happy_left);
              lcd.home();
              lcd.setCursor(9,0);
              lcd.write(0);
              lcd.createChar(1, happy_right);
              lcd.setCursor(5,0);
              lcd.print(t);
              delay (2000);
              lcd.setCursor(12,0);
              lcd.print("   ");
              lcd.setCursor(13,1);
              lcd.print("  ");
              lcd.createChar(0, left_reg);
              lcd.home();
              lcd.setCursor(9,0);
              lcd.write(0);
              lcd.createChar(1, right_reg);
              lcd.home();
              lcd.setCursor(10,0);
              lcd.write(1);
               if (t== levelLim)
               {
                levelNum= levelNum +1;
                t = 0;
                levelLim= 2*levelLim;
                clk=2*clk;
                lcd.setCursor(5,0);
                lcd.print(t);
                delay (3000);
                lcd.setCursor(7,1);
                lcd.print("     ");
                lcd.setCursor(0,1);
                lcd.print("level");
                lcd.setCursor(6,1);
                lcd.print(levelNum);
                break;
               }
              break;
            }
}
  
