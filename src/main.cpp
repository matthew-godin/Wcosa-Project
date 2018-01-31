//#include "Cosa/RTT.hh"
#include "Cosa/OutputPin.hh"
#include "Cosa/InputPin.hh"
#include "Cosa/Watchdog.hh"

//using namespace Board;

void blink(OutputPin pin, uint8_t times, uint16_t ms);
void sensorLoop();

OutputPin myLED(Board::D33);

OutputPin trigPin(Board::D23);
InputPin echoPin(Board::D25);

void setup() {
    //RTT::begin();
	Watchdog::begin();
}

void loop() {
	sensorLoop();
	Watchdog::delay(1000);
	/*blink(myLED, 3, 333);
	Watchdog::delay(1000);*/
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

int pulseIn()
{
	int us;

	while (true)
	{
		if (echoPin.is_on())
		{
			us = -Watchdog::millis() * 1000;
			break;
		}
	}
	while (true)
	{
		if (echoPin.is_off())
		{
			us += Watchdog::millis() * 1000;
			break;
		}
	}

	return us;
}

void sensorLoop()
{
    int distance, d, l1;
  
    trigPin.off();
    Watchdog::delay(0.002);
    trigPin.on();
    Watchdog::delay(0.01);
    trigPin.off();
    distance = pulseIn() * 0.034 / 2;
	if (distance > 100)
	{
		myLED.on();
	}
	else
	{
		myLED.off();
	}
}
