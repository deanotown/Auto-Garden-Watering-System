/********************************/
// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// set the variables
int temp; //not in use yet
int M_sensor1 = A0; //water moistur sensor
int relay1 = 12; //relay switch might change to a valve
int L_led = A2; //water level sensor not in use yet


/**********************************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
void setup()
{
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  lcd.begin(16,2); //set bit length
  lcd.clear(); //clear the LCD 
  pinMode (12,OUTPUT); // Relay Switch
  pinMode (0,INPUT); // Water moistur sensor
  pinMode (2,INPUT);// Water Level Sensor 
  pinMode (9,OUTPUT); // Speaker
  Serial.begin(9600); //Send data to serial monitor
  lcd.setCursor(0,1); //Set curson to first digit line 1
  lcd.print("Auto Garden"); 
  delay(2000); 
  lcd.clear(); 
  lcd.setCursor(0,0); //set cursor to first digit line 0
  lcd.print("Watering System"); 
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Initialising");
  delay(2500);
  lcd.clear();
  lcd.noBacklight(); //turn off backlight
  

  delay(1000);
  
  
}
/*********************************************************/



void loop() 
{

lcd.clear();

int Moisture1 =  analogRead(M_sensor1);//reads the value in the sensor
Serial.println(Moisture1);

if (Moisture1< 100)  //low variable for dry soil
  {
   lcd.clear();
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("Soil Dry");
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Initiate Pump");
   delay(1000); 
   digitalWrite(relay1,HIGH);
   delay(5000);
   digitalWrite(relay1,LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Verifying");
   delay(10000);
   
  }
if (Moisture1>= 100 && Moisture1<= 500)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Soil Fine");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Turn Pump Off");
    delay(1000);
    digitalWrite(relay1,LOW);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pump Off");
    delay(1000);
    lcd.clear();
    lcd.noBacklight();
  }

}
