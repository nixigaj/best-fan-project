#include <Arduino.h>

int main() {
    init();

    Serial.begin(115200);
    Serial.print("Initializing...");
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(3, OUTPUT);
    Serial.println(" Done");

    // Main program loop
    // ReSharper disable once CppDFAEndlessLoop
    //for (;;) {
    //	const int val = analogRead(A0);
    //	Serial.println(val/1023.0*5.0);
    //}


    analogWrite(3, 128);

    //analogWrite(11, 128);
    //for (int i = 0;; ++i) {
    //	analogWrite(3, i%255);
    //	delay(10);
    //}

    for (;;) {
        analogWrite(3, 0);
    }

    // Main program loop
    // ReSharper disable once CppDFAEndlessLoop
    //for (long i = 0;; ++i) {
    //	int val = analogRead(A0);
    //	double ratio = val/1023.0;

    //	int analogVal = (int)(ratio*255);

    //	analogWrite(3, analogVal);

    //	if (i % 1000 == 0) {
    //		Serial.println(ratio);
    //	}
    //	delay(1);
    //}
}
