//#include "Cosa/RTT.hh"
#include "Cosa/OutputPin.hh"
#include "Cosa/InputPin.hh"
#include "Cosa/Watchdog.hh"
#include "Cosa/AnalogPin.hh"
#include "Cosa/Trace.hh"
#include "Cosa/UART.hh"

//using namespace Board;

void blink(OutputPin pin, uint8_t times, uint16_t ms);
void sensorLoop();
void readBalluffPhotoelectric();

OutputPin myLED(Board::D33);

OutputPin trigPin(Board::D23);
InputPin echoPin(Board::D25);

AnalogPin analogPin(Board::A8);
InputPin pnpPin(Board::D24);

void setup() {
    //RTT::begin();
	uart.begin(9600);
	trace.begin(&uart, PSTR("TEST STARTED\n"));
	Watchdog::begin();
}

void loop() {
	
	//trace << "trace test" << endl;
	//TRACE("TEST\n");
	//sensorLoop();
	readBalluffPhotoelectric();
	Watchdog::delay(2000);
	/*blink(myLED, 3, 333);
	Watchdog::delay(1000);*/
    /*ledPin.on();
    delay(50);
    ledPin.off();
    delay(500);*/
}

void readBalluffPhotoelectric()
{
	analogPin.powerup();
	trace << analogPin.sample() << endl;
	analogPin.powerdown();
	trace << pnpPin.is_on() << endl;
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
