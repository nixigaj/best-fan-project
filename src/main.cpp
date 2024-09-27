#include <Arduino.h>

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(115200);
	Serial.println("setup()");
}

void loop() {
	Serial.println("loop()");
	digitalWrite(LED_BUILTIN, HIGH);
	delay( 64);
	digitalWrite(LED_BUILTIN, LOW);
	delay(128);
}
