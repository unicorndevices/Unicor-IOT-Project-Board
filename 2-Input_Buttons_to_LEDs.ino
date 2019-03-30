
/*//////////////////////////////////////////////////// 
///       UNICORN IOT PROJECT BOARD    ///////////////
//////////////////////////////////////////////////////
//////   LED Blinking ///////////////// 
 /* Steps:
 * 1: Upload code
 * 2: check LED 1, LED 2 and Built in LED on NODEMCU blinking with the delay of 1 sec 
 *
  */
 //////////////////////////////////////////////////////////////////////////////////////
 /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
 ////////////////////////////////////////////////////////////////////////////////////*/
#include <Arduino.h>
int led1_pin = 3;
int led2_pin = 1;
int BTN1_pin = 0;
int BTN2_pin = 2;

void setup() {
  pinMode(led1_pin, OUTPUT);     
  pinMode(led2_pin, OUTPUT);  
  pinMode(BTN1_pin, INPUT);
  pinMode(BTN2_pin, INPUT);

}
// the loop function runs over and over again forever
void loop() {
  if (digitalRead( BTN1_pin) == HIGH)
  {
    digitalWrite(led1_pin, HIGH);
  }
  if (digitalRead( BTN1_pin) == LOW)
  {
    digitalWrite(led1_pin, LOW);
  }
  if (digitalRead( BTN2_pin) == HIGH)
  {
    digitalWrite(led2_pin, HIGH);
  }
  if (digitalRead( BTN2_pin) == LOW)
  {
    digitalWrite(led2_pin, LOW);
  }                 
}
