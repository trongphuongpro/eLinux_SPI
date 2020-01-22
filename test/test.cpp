#include <iostream>
#include <unistd.h>
#include <cstring>
#include "spi.h"


using namespace std;
using namespace BBB;

int main() {
	SPI bus(SPI::SPI1, 100000);
	bus.setDataMode(SPI::MODE3);

	for (uint8_t i = 0; i <= 0x0F; i++) {
		bus.write(i);
		sleep(1);
	}
}