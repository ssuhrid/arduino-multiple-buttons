
#include "Arduino.h"
#include "EmButtons.h"

/*****************************************************************/

EmButtons::EmButtons(byte NUMBUTTONS,byte* buttonPin,unsigned char type){
    _type=type;
  _NUMBUTTONS=NUMBUTTONS;
  _buttonPin = new byte[_NUMBUTTONS];
  _pressed= new byte[_NUMBUTTONS];
   _justpressed=new byte[_NUMBUTTONS];
  _justreleased= new byte[_NUMBUTTONS];
  _previous_keystate = new byte[_NUMBUTTONS];
  _current_keystate = new byte[_NUMBUTTONS];
    _previousstate = new byte[_NUMBUTTONS];
  _currentstate = new byte[_NUMBUTTONS];

  for (int i=0;i<_NUMBUTTONS;i++){
    _buttonPin[i]=buttonPin[i];
    _pressed[i]=1;
    _justpressed[i]=1;
    _justreleased[i]=1;
    _previous_keystate[i]=1;
    _current_keystate[i]=1;
    _previousstate[i]=1;
    _currentstate[i]=1;
  }
  buttonInit();
}

void EmButtons::buttonInit(){
 for (int i=0;i<_NUMBUTTONS;i++){
  pinMode(_buttonPin[i],INPUT);
 }
}
void EmButtons::checkSwitches(){
//  static byte _previousstate[_NUMBUTTONS];
//  static byte _currentstate[_NUMBUTTONS];
//  static long _lasttime;
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
