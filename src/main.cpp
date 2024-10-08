#include <Arduino.h>

int main() {
	init();

	Serial.begin(115200);
	Serial.print("Initializing...");
	Serial.println(" Done");

	// Main program loop
	// ReSharper disable once CppDFAEndlessLoop
	for (long i = 0;; ++i) {
		int val = analogRead(A0);
		double ratio = val/1023.0;
		double temp = ratio * 20.0 + 15.0;

		//int analogVal = (int)(ratio*255);

		if (i % 1000 == 0) {
			Serial.println(temp);
		}
		delay(1);
	}
}
