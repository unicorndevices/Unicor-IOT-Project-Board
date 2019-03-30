/*////////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    ///////////////
  //////////////////////////////////////////////////////
  //////    Motion Sensor  /////////////////
  /* Steps:
   1: Upload code and place sensor 1 jumper
   2: Insert PIR sensor at sensor 1 place and enable relay 1
   3: Do some motion at front of PIR sensor and note the sound of relay 1
   4: Connect a fan or any load at relay 1 and check the load state after motion
*/
//////////////////////////////////////////////////////////////////////////////////////
/////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
////////////////////////////////////////////////////////////////////////////////////*/

const int PIRpin   = 0;
const int RELAYpin = 3;

void setup()
{
  pinMode(PIRpin, INPUT);
  pinMode(RELAYpin, OUTPUT);
  digitalWrite(RELAYpin, LOW);

}

void loop()
{
  if (digitalRead(PIRpin) == HIGH)    //Motion detected
  {
    digitalWrite(RELAYpin, HIGH);       //turn on the load
  }

  if (digitalRead(PIRpin) == LOW)    //No motion
  {
    digitalWrite(RELAYpin, LOW);        //turn OFF the load
  }

}
