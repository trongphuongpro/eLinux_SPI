#include <iostream>
#include <unistd.h>
#include <cstring>
#include "spi.h"
#include "crc32.h"

using namespace std;
using namespace BBB;

int main() {
	SPI bus(SPI::SPI1);
	bus.setMode(SPI::MODE0);

	crc32_init();

	/*const char *data[5] = {"codelungtung.com", "nguyentrongphuong", 
					"mr.trongphuongpro@gmail.com", "ntppro", "trongphuongpro"};

	for (uint8_t i = 0; i < 5; i++) {
		crc32_t crc = ~crc32_compute(data[i], strlen(data[i]));
		printf("CRC: %#x\n", crc);
		bus.write(0xBB);
		sleep(1);
		bus.write(strlen(data[i]));
		sleep(1);
		bus.writeBuffer(data[i], strlen(data[i]));
		bus.writeBuffer(&crc, sizeof(crc));
		sleep(1);
		bus.write(0xEE);
		sleep(1);
	}*/

	uint8_t data[100] = {0};

	for (uint8_t byte = 5; byte < 20; byte++) {
		bus.write(byte);
		usleep(100000);

		// read data
		bus.readBuffer(data, byte);
		// read crc32, two steps should be separated
		bus.readBuffer(data+byte, sizeof(crc32_t));

		for (uint8_t i = 0; i < byte; i++)
			printf("%c", data[i]);
		printf("\n0x");
		for (uint8_t i = 0; i < 4; i++)
			printf("%02x", data[byte+i]);

		printf("\n~CRC: %#x\n", ~crc32_compute(data, byte));

		if (crc32_check(data, byte + sizeof(crc32_t)) == 0)
			puts("Passed\n-----------");
		else
			puts("Failed\n-----------");
		usleep(500000);
	}

}