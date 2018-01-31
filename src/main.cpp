#include "Cosa/RTT.hh"
#include "Cosa/OutputPin.hh"
#include "Cosa/Watchdog.hh"

void blink(OutputPin pin, uint8_t times, uint16_t ms);
using namespace Board;

enum DigitalPin myPin = D31;

OutputPin myLED(myPin);

void setup() {
    RTT::begin();
	Watchdog::begin();
}

void loop() {
	blink(myLED, 3, 333);
	Watchdog::delay(1000);
    /*ledPin.on();
    delay(50);
    ledPin.off();
    delay(500);*/
}

void blink(OutputPin pin, uint8_t times, uint16_t ms) {
	for (uint8_t i = 0; i < times; ++i) {
		pin.on();
		Watchdog::delay(ms >> 1);
		pin.off();
		Watchdog::delay(ms >> 1);
	}
}
