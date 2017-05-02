
#ifndef EmButtons_h
#define EmButtons_h

#include "Arduino.h"

class EmButtons{

    #define DEBOUNCE 5

    public :

        EmButtons(uint8_t NUMBUTTONS,uint8_t* buttonPin,unsigned char type);
        void setSerialPrint(boolean p);
        byte switchJustPressed();
        void checkSwitches();
  
    private:

        void serialPrint(String s);        
        void buttonInit();

        char _type;
        boolean _print;
        uint8_t _NUMBUTTONS;
        uint8_t* _buttonPin;
        byte* _pressed, _justpressed, _justreleased;
        byte* _previous_keystate, _current_keystate;    
        unsigned long _lasttime;
        
};

#endif