#include <Arduino.h>

constexpr int AVG_TEMP_BUF_SIZE = 40;
constexpr unsigned long MIN_ON_TIME = 200;
constexpr unsigned long CYCLE_TIME = 2000;

double temp_buffer[AVG_TEMP_BUF_SIZE];
int buffer_index = 0;
bool buffer_filled = false;

double calc_avg_temp() {
	double sum = 0;
	const int count = buffer_filled ? AVG_TEMP_BUF_SIZE : buffer_index;
	for (int i = 0; i < count; i++) {
		sum += temp_buffer[i];
	}
	return sum / count;
}

int main() {
	init();
	Serial.begin(115200);
	pinMode(3, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);

	unsigned long prev_on_time = 0;
	int full_power_cycles_left = 0;

	bool fan_was_on = false;

	unsigned long loop_restart_time = micros();

	// Main program loop
	// ReSharper disable once CppDFAEndlessLoop
	for (long i = 0;; ++i) {
		const int temp_raw = analogRead(A1);
		const double temp_ratio = temp_raw / 1023.0;
		const double current_temp = temp_ratio * 20.0 + 15.0;

		temp_buffer[buffer_index] = current_temp;
		buffer_index = (buffer_index + 1) % AVG_TEMP_BUF_SIZE;
		if (buffer_index == 0) buffer_filled = true;

		const double temp = calc_avg_temp();

		const int pot_raw = analogRead(A0);
		const double pot_ratio = pot_raw / 1023.0;
		const double pot_temp = pot_ratio * 10.0 + 18.0;
		double temp_diff = temp - pot_temp;
		if (temp_diff < 0.0) {
			temp_diff = 0.0;
		}
		const double temp_diff_ratio = temp_diff / 10.0;
		unsigned long on_time = lround(temp_diff_ratio * CYCLE_TIME);

		if (on_time > 0 && on_time < MIN_ON_TIME) {
			on_time = 0;
		} else if (on_time > CYCLE_TIME) {
			on_time = CYCLE_TIME;
		}
		const unsigned long off_time = CYCLE_TIME - on_time;

		if (prev_on_time == 0 && on_time >= MIN_ON_TIME) {
			full_power_cycles_left = 20;
		}
		prev_on_time = on_time;

		if (pot_ratio == 1.0) {
			digitalWrite(10, LOW);
			digitalWrite(11, LOW);
			digitalWrite(12, LOW);
		} else if (pot_ratio >= 2.0 / 3.0) {
			digitalWrite(10, HIGH);
			digitalWrite(11, LOW);
			digitalWrite(12, LOW);
		} else if (pot_ratio >= 1.0 / 3.0) {
			digitalWrite(10, HIGH);
			digitalWrite(11, HIGH);
			digitalWrite(12, LOW);
		} else {
			digitalWrite(10, HIGH);
			digitalWrite(11, HIGH);
			digitalWrite(12, HIGH);
		}

		if (full_power_cycles_left > 0) {
			digitalWrite(3, HIGH);
			delayMicroseconds(CYCLE_TIME);
			full_power_cycles_left--;
			if (full_power_cycles_left == 0) {
				digitalWrite(3, LOW);
			}
		} else {
			const unsigned long calculation_time = micros() - loop_restart_time;

			if (fan_was_on) {
				if (calculation_time > on_time) {
					digitalWrite(3, LOW);
					delayMicroseconds(off_time - (calculation_time - on_time));
					fan_was_on = false;
				} else {
					delayMicroseconds(on_time - calculation_time);
					digitalWrite(3, LOW);
					delayMicroseconds(off_time);
					digitalWrite(3, HIGH);
					fan_was_on = true;
				}
			} else {
				if (calculation_time > off_time) {
					digitalWrite(3, HIGH);
					delayMicroseconds(on_time - (calculation_time - off_time));
					fan_was_on = true;
				} else {
					delayMicroseconds(off_time - calculation_time);
					digitalWrite(3, HIGH);
					delayMicroseconds(on_time);
					digitalWrite(3, LOW);
					fan_was_on = false;
				}
			}
		}

		loop_restart_time = micros();

		if (i % 500 == 0) {
			Serial.println(pot_temp);
			Serial.println(temp);
			Serial.println(static_cast<double>(on_time) / 2000.0);
			Serial.println();
		}
	}
}
