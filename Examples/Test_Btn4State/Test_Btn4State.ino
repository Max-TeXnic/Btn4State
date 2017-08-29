#include <Btn4State.h>

#define BTN_PIN 8

Btn4State btn = Btn4State(BTN_PIN);

void setup() {
    Serial.begin(115200);
    Serial.println("Started");
}

void loop() {
    int b = btn.readState();
    if (b == BTN_CLICK) Serial.println("single click");
    if (b == BTN_DOUBLE_CLICK) Serial.println("double click");
    if (b == BTN_HOLD) Serial.println("press and hold");
    if (b == BTN_LONG_HOLD) Serial.println("long press and hold");
}
