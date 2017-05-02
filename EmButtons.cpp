
#include "Arduino.h"
#include "EmButtons.h"

/*****************************************************************/

EmButtons::EmButtons(uint8_t NUMBUTTONS;uint8_t arr[],char type){
  _buttonPin=arr;
  _type=type;
  _NUMBUTTONS=NUMBUTTONS;
  buttonInit();
}
void EmButtons::buttonInit(){
 for (int i=0;i<_NUMBUTTONS;i++){
  pinMode(_buttonPin[i],INPUT);
 }
}
void EmButtons::checkSwitches(){
  static byte _previousstate[NUMBUTTONS];
  static byte _currentstate[NUMBUTTONS];
  static long _lasttime;
  byte index;
  if (millis() < _lasttime) {
    // we wrapped around, lets just try again
    _lasttime = millis();
  }
  if ((_lasttime + DEBOUNCE) > millis()) {
    // not enough time has passed to debounce
    return; 
  }
  // ok we have waited DEBOUNCE milliseconds, lets reset the timer
  _lasttime = millis();
  for (index = 0; index < _NUMBUTTONS; index++) {
    _justpressed[index] = 0;       //when we start, we clear out the "just" indicators
    _justreleased[index] = 0;
    _currentstate[index] = digitalRead(_buttonPin[index]);   //read the button
    if (_currentstate[index] == _previousstate[index]) {
      if ((_pressed[index] == LOW) && (_currentstate[index] == LOW)) {
        // just pressed
        _justpressed[index] = 1;
      }
      else if ((_pressed[index] == HIGH) && (_currentstate[index] == HIGH)) {
        _justreleased[index] = 1; // just released
      }
      _pressed[index] = !_currentstate[index];  //remember, digital HIGH means NOT pressed
    }
    _previousstate[index] = _currentstate[index]; //keep a running tally of the buttons
  }
}

byte EmButtons::switchJustPressed() {
  byte thisSwitch = 255;
  checkSwitches();  //check the switches &amp; get the current state
  for (byte i = 0; i < _NUMBUTTONS; i++) {
    _current_keystate[i]=_justpressed[i];
    if (_current_keystate[i] != _previous_keystate[i]) {
      if (_current_keystate[i]) thisSwitch=i;
    }
    _previous_keystate[i]=_current_keystate[i];
  }  
  return thisSwitch;
}

//=============================================================//

void EmSevenSegment::setSerialPrint(boolean p){
  _print=p;
}

/*****************************************************************/


void EmSevenSegment::serialPrint(String s){
  if (_print==true)
    Serial.println(s);
}

/*****************************************************************/

/*void EmButtons::test(){
  int arr[_digits];
  for(int i=0;i<10;i++){
    for(int j=0;j<_digits;j++){
      arr[j]=i;
    }
    writeArray(arr);
    delay(100);
  }
}*/

/*****************************************************************/

/*****************************************************************/