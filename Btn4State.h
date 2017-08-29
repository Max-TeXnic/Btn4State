/*----------------------------------------------------------------------*
 * Arduino Button 4-State Library v0.1                                  *
 *----------------------------------------------------------------------*/
 #ifndef Btn4State_h
 #define Btn4State_h
 #if ARDUINO >= 100
 #include <Arduino.h> 
 #else
 #include <WProgram.h> 
 #endif

#define BTN_UNDEFINED 0
#define BTN_CLICK 1
#define BTN_DOUBLE_CLICK 2
#define BTN_HOLD 3
#define BTN_LONG_HOLD 4

 class Btn4State
 {
     public:
         Btn4State(uint8_t pin);
         int readState();   
     private:
         uint8_t _pin;           //arduino pin number
         // Button timing variables
        int _debounce;          // ms debounce period to prevent flickering when pressing or releasing the button
        int _DCgap;            // max ms between clicks for a double click event
        int _holdTime;        // ms hold period: how long to wait for press+hold event
        int _longHoldTime;    // ms long hold period: how long to wait for press+hold event
        // Button variables
        boolean _buttonVal;   // value read from button
        boolean _buttonLast;  // buffered value of the button's previous state
        boolean _DCwaiting;  // whether we're waiting for a double click (down)
        boolean _DConUp;     // whether to register a double click on next release, or whether to wait and click
        boolean _singleOK;    // whether it's OK to do a single click
        long _downTime;         // time the button was pressed down
        long _upTime;           // time the button was released
        boolean _ignoreUp;   // whether to ignore the button release because the click+hold was triggered
        boolean _waitForUp;        // when held, whether to wait for the up event
        boolean _holdEventPast;    // whether or not the hold event happened already
        boolean _longHoldEventPast;// whether or not the long hold event happened already
 };
 #endif