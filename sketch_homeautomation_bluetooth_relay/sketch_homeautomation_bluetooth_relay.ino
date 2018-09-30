/*
  Home Automation with Bluetooth card and 8-channel Relay

  By Ellai Information Systems Pvt Ltd

  This example code is in the public domain.
  https://github.com/ellaisys/arduino_bluetooth_relay
*/


#include <SoftwareSerial.h>

#define PIN_RX 0
#define PIN_TX 1

SoftwareSerial sensor(PIN_RX, PIN_TX); // RX, TX
const int digitalPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int cointPins = 0;

// Put your setup code here, to run once
void setup() {
  Serial.begin(9600); 
  sensor.begin(9600);

  //Calculate array length count
  cointPins = sizeof(digitalPins) / sizeof(digitalPins[0]);

  //Set ditital pin mode
  for (int x=0; x < cointPins; x++){
    pinMode(digitalPins[x], OUTPUT);
    digitalWrite(digitalPins[x], LOW);
  } //Loop ends

  delay(500);
} //Function ends

// Put your main code here, to run repeatedly:
void loop() {  
  if(Serial.available()>0) {   
    String data = Serial.readString();
    data.toUpperCase();

    //Get index of the token (used hyphen '-' character here)
    int index = data.indexOf('-');
    if(index>0) {
      String btnPin = data.substring(0, index);
      
      int pinInput = btnPin.toInt();
      pinInput = pinInput-1; //Adjust array length
      
      int btnState = ((data.indexOf('ON'))>=0)?HIGH:LOW;
      if(pinInput>=0) {
        //Read current pin status
        int pinStatus = digitalRead(digitalPins[pinInput]);
  
        //Toggle and write to pin
        digitalWrite(digitalPins[pinInput], btnState);      
      } //End if
    } //End if

  } //End if
} //Function ends
