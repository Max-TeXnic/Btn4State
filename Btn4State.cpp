#include <Btn4State.h>

Btn4State::Btn4State(uint8_t pin)
{
    _pin = pin;
    // Button timing variables
    _debounce = 10;
    _DCgap = 500;
    _holdTime = 2000;
    _longHoldTime = 5000;

    // Button variables
    _buttonVal = HIGH;
    _buttonLast = HIGH;
    _DCwaiting = false;
    _DConUp = false;
    _singleOK = true;
    _downTime = -1;
    _upTime = -1;
    _ignoreUp = false;
    _waitForUp = false;
    _holdEventPast = false;
    _longHoldEventPast = false;

    pinMode(_pin, INPUT_PULLUP); //
}

int Btn4State::readState()
{
    int event = BTN_UNDEFINED;
    _buttonVal = digitalRead(_pin);
    // Button pressed down
    if (_buttonVal == LOW && _buttonLast == HIGH && (millis() - _upTime) > _debounce)
    {
        _downTime = millis();
        _ignoreUp = false;
        _waitForUp = false;
        _singleOK = true;
        _holdEventPast = false;
        _longHoldEventPast = false;
        if ((millis()-_upTime) < _DCgap && _DConUp == false && _DCwaiting == true) _DConUp = true;
        else  _DConUp = false;
        _DCwaiting = false;
    }
    // Button released
    else if (_buttonVal == HIGH && _buttonLast == LOW && (millis() - _downTime) > _debounce)
    {        
        if (not _ignoreUp)
        {
            _upTime = millis();
            if (_DConUp == false) _DCwaiting = true;
            else
            {
                event = BTN_DOUBLE_CLICK;
                _DConUp = false;
                _DCwaiting = false;
                _singleOK = false;
            }
        }
    }
    // Test for normal click event: DCgap expired
    if (_buttonVal == HIGH && (millis()-_upTime) >= _DCgap && _DCwaiting == true && _DConUp == false && _singleOK == true && event != 2)
    {
        event = BTN_CLICK;
        _DCwaiting = false;
    }
    // Test for hold
    if (_buttonVal == LOW && (millis() - _downTime) >= _holdTime) {
        // Trigger "normal" hold
        if (not _holdEventPast)
        {
            event = BTN_HOLD;
            _waitForUp = true;
            _ignoreUp = true;
            _DConUp = false;
            _DCwaiting = false;
            //downTime = millis();
            _holdEventPast = true;
        }
        // Trigger "long" hold
        if ((millis() - _downTime) >= _longHoldTime)
        {
            if (not _longHoldEventPast)
            {
                event = BTN_LONG_HOLD;
                _longHoldEventPast = true;
            }
        }
    }
    _buttonLast = _buttonVal;
    return event;
 }