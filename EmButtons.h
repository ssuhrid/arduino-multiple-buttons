
#ifndef EmButtons_h
#define EmButtons_h

#include "Arduino.h"

class EmButtons{

    #define DEBOUNCE 5

    public :

        EmButtons(uint8_t NUMBUTTONS,uint8_t buttonsPin[],char type);
        void test();
        void setSerialPrint(boolean p);
        byte switchJustPressed();
        void checkSwitches();
  
    private:
        uint8_t _NUMBUTTONS;
        uint8_t _buttonPin[];
        byte _pressed[_NUMBUTTONS], _justpressed[_NUMBUTTONS], _justreleased[_NUMBUTTONS];
        byte _previous_keystate[_NUMBUTTONS], _current_keystate[_NUMBUTTONS];

        unsigned long _lasttime;
        void serialPrint(String s);        
        char _type;
        boolean _print;
};

#endif