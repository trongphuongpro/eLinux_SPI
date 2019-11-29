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

	const char *data[5] = {"codelungtung.com", "nguyentrongphuong", 
					"mr.trongphuongpro@gmail.com", "ntppro", "trongphuongpro"};

	for (uint8_t i = 0; i < 5; i++) {
		crc32_t crc = crc32_compute((uint8_t*)data[i], strlen(data[i]));
		printf("%#x\n", crc);
		bus.write(0xBB);
		sleep(1);
		//bus.write(strlen(data[i]) + sizeof(crc));
		sleep(1);
		//bus.writeBuffer((uint8_t*)data[i], strlen(data[i]));
		//bus.writeBuffer((uint8_t*)&crc, sizeof(crc));
		sleep(1);
		bus.write(0xEE);
		sleep(1);
	}

}