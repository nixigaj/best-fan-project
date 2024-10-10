#include <Arduino.h>

int main() {
	init();

	Serial.begin(115200);
	Serial.print("Initializing...");
	Serial.println(" Done");

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(3, OUTPUT);
    Serial.println(" Done");


	// Main program loop
	// ReSharper disable once CppDFAEndlessLoop
	for (long i = 0;; ++i) {
		int tempRaw = analogRead(A1);
		double tempRatio = tempRaw/1023.0;
		double temp = tempRatio * 20.0 + 15.0;
		int potRaw = analogRead(A0);
    	double potRatio = potRaw/1023.0;
		double potTemp = potRatio * 10.0 + 18.0;

        double tempDiff = temp - potTemp;
		double tempDiffRatio = tempDiff / 10.0;
		if (tempDiff < 0.0) {
			tempDiff = 0.0;
		}

        int onTime = round(tempDiff * 10.0);

		if (onTime > 10) {
			onTime = 10;
		}

		int offTime = 10 - onTime;

		digitalWrite(3, HIGH);
		delay(onTime);
		digitalWrite(3, LOW);
		delay(offTime);


    	if (i % 100 == 0) {
			Serial.println(temp);
    		Serial.println(potTemp);
            Serial.println(onTime);
            Serial.println();
    	}
	}
}
