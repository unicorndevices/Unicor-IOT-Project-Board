/*////////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    ///////////////
  //////////////////////////////////////////////////////
  //////   LED Blinking /////////////////
  /* Steps:
   1: Upload code
   2: check LED 1, LED 2 and Built in LED on NODEMCU blinking with the delay of 1 sec

*/
//////////////////////////////////////////////////////////////////////////////////////
/////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
////////////////////////////////////////////////////////////////////////////////////*/
int led1_pin = 1;
int led2_pin = 3;
int led3_pin = 2;

void setup() {
  pinMode(led1_pin, OUTPUT);        // Initialize the LED1 pin as an output
  pinMode(led2_pin, OUTPUT);        // Initialize the LED2 pin as an output
  pinMode(led3_pin, OUTPUT);        // Initialize the Built-in LED pin as an output
}
// the loop function runs over and over again forever
void loop() {
  digitalWrite(led1_pin, LOW);      // Turn the LED off
  digitalWrite(led2_pin, LOW);
  digitalWrite(led3_pin, HIGH);     // Turn the LED off (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because
  delay(1000);                      // Wait for a second
  digitalWrite(led1_pin, HIGH);     //turn the LED on
  digitalWrite(led2_pin, HIGH);
  digitalWrite(led3_pin, LOW);      //turn the LED on (inverted Logic for BUILT-IN LED)
  delay(1000);                      // Wait for a seconds (to demonstrate the active low LED)
}
