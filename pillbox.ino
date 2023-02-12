#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;  
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// SCL A5
// SDA A4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
void setup()   {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(6,INPUT_PULLUP);  //Switch
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.display();
  display.clearDisplay();
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(WHITE);
    display.setCursor(0, 25);
    display.println("Pill Box");
    display.display();
    delay(2000);
}
int poz=1;
int broj=1;
int kretanjeY=30;
 
int sec1=0;
int min1=0;
unsigned long msec=0;
unsigned long mili=0;
int pres=0;
int fase=0;
int start=0;
unsigned long tim=0;
void loop()
  {
      display.clearDisplay();
      if(digitalRead(6)==0)
      {
        if(pres==0)
           {
            fase=fase+1;
            pres=1;
            if(fase>1)
            fase=0;
            }
        }else{pres=0;}
 
     if(fase==0)
      {
      display.setFont(&FreeSans9pt7b);
      display.setFont();
      display.setCursor(33, 15);
      display.println("DIPENSED");
      display.setFont(&FreeSans12pt7b);
      display.setFont();
      display.setCursor(30,35);
      display.print("Place medication back for next dose");
      
      sec1=0;
      min1=0;
      tim=0;
      mili=0;
      msec=0;
      start=0;
      }
 
      if(fase==1)
      {
        display.clearDisplay();
        display.setFont(&FreeSans12pt7b);
        display.setFont();
        display.setCursor(37,0);
        display.print("Stopwatch");
        display.setFont(&FreeSans9pt7b);
        
        if(start==0)
          {
            start=1;
            tim=millis();  
          }
       msec=(millis()-tim); 
   
        min1=msec/60000;
            
        if((msec/1000)>59)
           {
            sec1=(msec/1000)-(min1*60);
            }else{
              sec1=msec/1000;
              }
 
          mili=(msec%1000)/10;
      
           display.setCursor(42,30);
           if(min1<=9)
           {
            display.print("0");
            display.print(min1);
            }else {display.print(min1);}
 
            display.print(":");
 
             if(sec1<=9)
           {
            display.print("0");
            display.print(sec1);
            }else {display.print(sec1);}
            display.setFont(&FreeSans12pt7b);
            display.setCursor(50,57);
 
                  if(mili<=9)
           {
            display.print("0");
            display.print(mili);
            }else {display.print(mili);}   
            if (min1==1)
            { myservo.write(90); //lockbox opened 

            } else {myservo.write(0);} //lockboxlocked
       }
 

  
      display.display();

  }