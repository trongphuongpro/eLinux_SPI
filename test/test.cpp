#include <iostream>
#include <unistd.h>
#include "spi.h"


using namespace std;
using namespace BBB;

int main() {
	SPI bus(SPI::SPI1);
	bus.setMode(SPI::MODE0);

	for (uint8_t i = 0; i < 0xFF; i++) {
		bus.write(i);
		usleep(100000);
	}
}