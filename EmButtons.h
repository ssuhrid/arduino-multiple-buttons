
#ifndef EmButtons_h
#define EmButtons_h

#include "Arduino.h"

class EmButtons{

    #define DEBOUNCE 5

    public :

        EmButtons(byte NUMBUTTONS,byte* buttonPin,byte type);
        byte switchJustPressed();
        void checkSwitches();
  
    private:

        void buttonInit();

        char _type;
        byte _NUMBUTTONS;
        byte* _buttonPin;
        byte* _pressed;
        byte* _justpressed;
        byte* _justreleased;
        byte* _previous_keystate;
        byte* _current_keystate; 
        byte* _previousstate;
        byte* _currentstate;
        unsigned long _lasttime;
           
};

#endif