// include the library code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/**********************************************************/
// set the global variables
//int temp; //not in use yet
//int L_led = A2; //water level sensor not in use yet

int M_sensor1 = A0; //water moistur sensor
int relay1 = 12; //relay switch might change to a valve
int LCDtxtdelay = 2000; //set text delay default to 2000
int relay1counter = 5000; //set how long relay on for for future hardware use
String LCDtxt; //stores string of text


/**********************************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

/**********************************************************/
void setup()
{
  Serial.begin(9600); //Send data to serial monitor

  pinMode (12,OUTPUT); // Relay Switch
  pinMode (0,INPUT); // Water moistur sensor
    
  lcd.init(); //initialize the lcd

// playwelcome message and clear
  LCDtxt=("Auto Garden","Watering System"); 
  setLCD();
  LCDtxt=("Initialising");
  setLCD();
  lcd.clear();
  lcd.noBacklight(); 
}

/*********************************************************/
void loop() 
{
lcd.clear();
int Moisture1 =  analogRead(M_sensor1); //reads the value in the sensor
int state = 1; //1 is watered and 0 is not watered.

Serial.println(Moisture1);

  if (Moisture1< 100)  //low variable for dry soil
  {   
   state = 0;
   WaterPumpCycle();
   LCDtxt=("Verifying");
   setLCD();
   delay(9000);
  
  else if (Moisture1>= 100 && state == 0)
  {
    LCDtxt=("Soil Fine");
    setLCD();
    digitalWrite(relay1,LOW);
    LCDtxt=("Pump Off");
    setLCD();
    lcd.clear();
    lcd.noBacklight();
    state = 1; //set   
  }
 else
 {
     lcd.clear();
     lcd.noBacklight(); 
 }
  }

/**********************************************************/
void setLCD() //custom function
{
lcd.clear(); 
lcd.backlight(); 
lcd.setCursor(0,0);
lcd.print(LCDtxt);
delay(LCDtxtdelay); 
}

void WaterPumpCycle() //custom function to turn on pump
{
LCDtxt=("Soil Dry");
setLCD();
LCDtxt=("Pump on");
setLCD();
digitalWrite(relay1,HIGH);
delay(relay1counter);
digitalWrite(relay1,LOW);
lcd.clear();
}
