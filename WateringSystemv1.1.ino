/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// set the global variables
int temp; //not in use yet
int M_sensor1 = A0; //water moistur sensor
int relay1 = 12; //relay switch might change to a valve
int L_led = A2; //water level sensor not in use yet
String LCDtxt; //stores string of text


/**********************************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
void setup()
{
  Serial.begin(9600); //Send data to serial monitor

  pinMode (12,OUTPUT); // Relay Switch
  pinMode (0,INPUT); // Water moistur sensor
  pinMode (2,INPUT);// Water Level Sensor not in use
  pinMode (9,OUTPUT); // Speaker not in use
  
  lcd.init(); //initialize the lcd
  LCDtxt=("Auto Garden");
  setLCD();
  LCDtxt=("Watering System"); 
  setLCD();  
  LCDtxt=("Initialising");
  setLCD();
  lcd.clear();
  lcd.noBacklight(); //turn off backlight
}

/*********************************************************/

void loop() 
{
lcd.clear();
int Moisture1 =  analogRead(M_sensor1);//reads the value in the sensor
Serial.println(Moisture1);

  if (Moisture1< 100)  //low variable for dry soil
  {
   
   LCDtxt=("Soil Dry");
   setLCD();   
   LCDtxt=("Initiate Pump");
   setLCD();   
   digitalWrite(relay1,HIGH);
   delay(5000);
   digitalWrite(relay1,LOW);
   LCDtxt=("Verifying");
   setLCD();
   delay(9000);
  }
  
  if (Moisture1>= 100 && Moisture1<= 500)
  {
    LCDtxt=("Soil Fine");
    setLCD();
    LCDtxt=("Turn Pump Off");
    setLCD();
    digitalWrite(relay1,LOW);
    LCDtxt=("Pump Off");
    setLCD();
    lcd.clear();
    lcd.noBacklight();
  }
}

void setLCD() //custom function
{
lcd.clear(); //clear the LCD 
lcd.backlight(); //open the backlight
lcd.setCursor(0,0); //Set curson to first digit line 1
lcd.print(LCDtxt);
delay(2000);
//i need to turn the light off after routine has finished - 
}
