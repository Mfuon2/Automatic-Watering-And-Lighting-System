#include <Wire.h>
#include "rgb_lcd.h"  
#include <SD.h>  

File myFile;
rgb_lcd lcd;

int Value,moist=A0;
int switchPin=10;

void setup()  
{  
  pinMode(moist,INPUT);
  pinMode(switchPin,OUTPUT);
  pinMode(13,OUTPUT);       //settingup the LEDs to the respective pins
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
// Some time to open serial monitor   
  
// Open serial communications and wait for port to open:
  lcd.begin(16,2);  
  Serial.begin(9600);  
  while (!Serial) {  
    ; // wait for serial port to connect. Needed for Leonardo only  
  }  
  
  Serial.print("Initializing SD card...");  
  
  // open the file. note that only one file can be open at a time,  
  // so you have to close this one before opening another.  
  myFile = SD.open("test.txt", FILE_WRITE);  
  
}  
  
void loop()  
{  
  Value = analogRead(moist);
    // nothing happens after setup
   myFile = SD.open("test.txt", FILE_WRITE);  
    
    // if the file opened okay, write to it:
  if(Value > 1020){ 
  if (myFile) {  
    Serial.println("SENSOR NOT CONNECTED");
    myFile.print(",SENSOR_NOT_CONNECTED,");
    myFile.print(Value);
    myFile.print(".");
    // close the file:  
    myFile.close();  
    //Serial.println("done.");  
  } else {  
    // if the file didn't open, print an error:  
    Serial.println("error opening test.txt");  
  }
  //Relay pins
  digitalWrite(switchPin,LOW);
  digitalWrite(13,HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  lcd.print("Moisture Sensor");
  delay(1000);
  lcd.clear();
  lcd.print("Disconected");
  delay(1000);
  lcd.clear();
  }   
  // if the file opened okay, write to it:
  if(Value > 700 && Value < 1020){ 
  if (myFile) {  
    Serial.println("THE SOIL MOISTURE CONTENT IS LOW POWER THE PUMP");
    myFile.print(",LOW_MOISTURE,");
    myFile.print(Value);
    myFile.print(".");
    // close the file:  
    myFile.close();  
    //Serial.println("done.");  
  } else {  
    // if the file didn't open, print an error:  
    Serial.println("error opening test.txt");  
  }
  //Relay pins
  digitalWrite(switchPin,HIGH);
  Serial.println("THE SOIL MOISTURE CONTENT IS LOW POWER THE PUMP");
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  lcd.print("Caution:Pump On");
  delay(1000);
  lcd.clear(); 
  }    
  // if the file opened okay, write to it:
  else if(Value > 400 && Value < 699){ 
  if (myFile) {  
    Serial.println("THE SOIL IS HUMID: GOOD CONDITION FOR THE FARM");  
    myFile.print(",HUMID_CONDITION,");
    myFile.print(Value);
    myFile.print(".");
    // close the file:  
    myFile.close();  
    //Serial.println("done.");  
  } else {  
    // if the file didn't open, print an error:  
    Serial.println("error opening test.txt");  
  }
  //Relay pins
  digitalWrite(switchPin,LOW);
  //Serial.println("The Soil Is i a Humid Condition");
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  lcd.print("SOIL HUMID");
  delay(1000);
  lcd.clear();
  lcd.print("GOOD CONDITION");
  delay(1000);
  lcd.clear();
  
  } 
  // if waterloged
 //else(Value > 0 && Value < 399)
else{ 
  if (myFile) {  
    Serial.println("WATER PLEASE DISCONNECT THE PUMP");    
    myFile.print(",WATER_LOGGED,");
    myFile.print(Value);
    myFile.print(".");
    // close the file:  
    myFile.close();  
    Serial.println("done.");  
  } else {  
    // if the file didn't open, print an error:  
    Serial.println("error opening test.txt");  
  }
  //Relay pins
  digitalWrite(switchPin,LOW);
  //Serial.println("The Soil Is Water Logged");
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  lcd.print("WATER LOGGED");
  delay(1000);
  lcd.clear();
  lcd.print("DISCONECT PUMP");
  delay(1000);
  lcd.clear();
  }       
  delay(1000);
}  
