
/*//////////////////////////////////////////////////// 
///       UNICORN IOT PROJECT BOARD    ///////////////
//////////////////////////////////////////////////////
//////   Input Buttons to LEDs ///////////////// 
 /* Steps:
  1: Upload code
  2.	Press BT1 and check LED1 state.
  3.	Press BT2 and check LED2 state.
  4.	Place R1, R2 and BZ jumpers to enable relay 1, relay 2 and buzzer respectively.
  5.	Connect any load with relay 1 or relay 2 and control it with buttons.

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
