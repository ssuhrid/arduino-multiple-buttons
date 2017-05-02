#include <EmButtons.h>
 
byte buttonPin[] = {2,3,4}; 
EmButtons emB(3,&buttonPin[0]);
  
void setup() {
  Serial.begin(9600); //set up serial port
  Serial.print("start");
}
 
void loop() {
  byte thisSwitch=emB.switchPressed();
  if (thisSwitch!=255)
    Serial.print(thisSwitch);
}