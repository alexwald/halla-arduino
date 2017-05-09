/*

 The circuit:
 * RX is digital pin 11 (connect to TX of other device)
 * TX is digital pin 12 (connect to RX of other device)

 */

#define DEBUG 1

#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.print (x)
 #define DEBUG_PRINTLN(x)  Serial.println (x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
#endif

#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12);
int led = 9;           // the PWM pin 
int redLed = 3;           // the PWM pin
int yellowLed = 5;           // the PWM pin
int greenLed = 6;           // the PWM pin


int brightness = 0;    // how bright the LED is
String inString = "";    // string to hold input

void setup() {
  pinMode(led, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
 
      mySerial.println("SET BT NAME Arduino_BT");
        Serial.begin(9600);                      // connect to the serial port
         mySerial.println("AT + NAMESvietidlo");
      mySerial.write("AT + NAMESvietidlo");

      Serial.println("SET BT NAME Arduino_BT");
}

void loop() {

////// COMM IONLY
//char c;
//  if (Serial.available()) {
//    c = Serial.read();
//    mySerial.print(c);
//  }
//  if (mySerial.available()) {
//    c = mySerial.read();
//    Serial.print(c);    
//  }

//////

  
    int inChar = mySerial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      DEBUG_PRINT("Value:");
      DEBUG_PRINTLN(inString.toInt());

      brightness = inString.toInt();
      
      if (brightness >= 0 && brightness <= 255) {
        analogWrite(led, brightness);
      } else if (brightness >= 256 && brightness <= 511) {
          DEBUG_PRINT("assigning redValue: ");
          DEBUG_PRINT(brightness-256);
        analogWrite(redLed, brightness-256);
      } else if  (brightness >= 512 && brightness <= 767) {
        DEBUG_PRINT("assigning yellowValue: ");
        DEBUG_PRINT(brightness-256);
        analogWrite(yellowLed, brightness-256);
      } else if  (brightness >= 768 && brightness <= 1023) {
        DEBUG_PRINT("assigning yellowValue: ");
        DEBUG_PRINT(brightness-256);
        analogWrite(greenLed, brightness-256);
      }
      
      DEBUG_PRINT("String: ");
      DEBUG_PRINTLN(inString);
      // clear the string for new input:
      inString = "";
    } 
}

