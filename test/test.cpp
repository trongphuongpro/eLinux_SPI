#include <iostream>
#include <unistd.h>
#include <cstring>
#include "spi.h"


using namespace std;
using namespace BBB;

int main() {
	SPI bus(SPI::SPI1, 500000);
	bus.setDataMode(SPI::MODE3);

	puts("Running...");

	uint8_t data[10] = {1,2,3,4,5,6,7,8,9,0};
	while (1) {
		bus.writeBuffer(data, 10);
		sleep(1);
	}

	// uint8_t buffer[30];

	// while (1) {
	// 	bus.readBuffer(buffer, 23);
	// 	printf("Received:");
	// 	for (int i = 0; i < 23; i++) {
	// 		printf("%c", buffer[i]);
	// 	}
	// 	printf("\n");

	// 	sleep(2);
	// }
}