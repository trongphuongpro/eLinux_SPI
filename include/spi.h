#ifndef __SPI__
#define __SPI__

#include <cstdint>
#include <string>

#define SPI_PATH	"/dev/spidev"

namespace BBB {

class SPI {
public:
	enum SPI_MODE {MODE0=0, MODE1, MODE2, MODE3};
	enum SPI_BUS {SPI0=1, SPI1=2};

	SPI(SPI_BUS bus);
	~SPI();

	int open();
	void close();

	uint8_t read();
	uint8_t* readBuffer(int num);

	int write(uint8_t value);
	int writeBuffer(uint8_t* buffer, int num);

	int setSpeed(uint32_t speed);
	int setMode(SPI_MODE mode);
	int setBitsPerWord(uint8_t bits);

private:
	int file;
	std::string filename;
	uint8_t bits;
	uint32_t speed;
	uint16_t delay;
	SPI_MODE mode;

	int transfer(uint8_t* txBuffer, uint8_t* rxBuffer, int num);

};

} /* namespace BBB */

#endif /* __SPI__ */