#include <Arduino.h>

int main() {
	init();

	Serial.begin(115200);
	Serial.print("Initializing...");
	pinMode(LED_BUILTIN, OUTPUT);
	Serial.println(" Done");

	// Main program loop
	// ReSharper disable once CppDFAEndlessLoop
	for (;;) {
		digitalWrite(LED_BUILTIN, LOW);
		delay(128);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(64);
	}
}
