/*

 The circuit:
 * RX is digital pin 11 (connect to TX of other device)
 * TX is digital pin 12 (connect to RX of other device)
 */

#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12);
int led = 9;           // the PWM pin 
int redLed = 3;           // the PWM pin
int yellowLed = 5;           // the PWM pin
int greenLed = 6;           // the PWM pin

int ledCount = 4;           // internal protocol for LED count discovery

int brightness = 0;    // how bright the LED is
String inString = "";    // string to hold input

void setup() {
  pinMode(led, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
 
  Serial.begin(9600);                      // connect to the serial port

  setName();
}

void loop() {
  int inChar = mySerial.read();

    //internal protocol for LED count discovery
    if (inChar == 'q'){
       mySerial.print(ledCount);
       Serial.print(ledCount);
    }
    
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    } 
    // if we get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());

      brightness = inString.toInt();
      
      if (brightness >= 0 && brightness <= 255) {
        analogWrite(led, brightness);
      } else if (brightness >= 256 && brightness <= 511) {
          Serial.print("assigning redValue: ");
          Serial.print(brightness-256);
        analogWrite(redLed, brightness-256);
      } else if  (brightness >= 512 && brightness <= 767) {
        Serial.print("assigning yellowValue: ");
        Serial.print(brightness-256);
        analogWrite(yellowLed, brightness-256);
      } else if  (brightness >= 768 && brightness <= 1023) {
        Serial.print("assigning yellowValue: ");
        Serial.print(brightness-256);
        analogWrite(greenLed, brightness-256);
      }
      
      Serial.print("String: ");
      Serial.println(inString);
      // clear the string for new input:
      inString = "";
    } 
}

void setName() {
  String nameValue = "";

  if (ledCount > 2) {
    nameValue = "Halla360";
  } else {
      nameValue = "Halla180";
  }
  
  String command(F("AT+NAME"));
  command += nameValue;
  doCommandAndEchoResult(command.c_str());
}

void doCommandAndEchoResult(const char * command)
//void doCommandAndEchoResult(const char * command, const __FlashStringHelper * meaning)

{
  // announce command
  Serial.print(F("Sending command: "));
  Serial.print(command);
//  if (meaning != NULL)
//  {
//    Serial.print(F(" ("));
//    Serial.print(meaning);
//    Serial.print(F(")"));
//  }
  Serial.println();

  // send command
    mySerial.print(command);
     Serial.print(command);

  // normalize line end
    Serial.println();
}

