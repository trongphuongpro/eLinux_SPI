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

	virtual int open();
	virtual void close();

	virtual uint8_t read();
	virtual uint8_t read(uint8_t reg);
	virtual uint8_t* readBuffer(uint16_t num);
	virtual uint8_t* readBuffer(uint8_t reg, uint16_t num);

	virtual int write(uint8_t value);
	virtual int write(uint8_t reg, uint8_t value);
	virtual int writeBuffer(uint8_t* buffer, uint16_t num);
	virtual int writeBuffer(uint8_t reg, uint8_t* buffer, uint16_t num);

	virtual int setSpeed(uint32_t speed);
	virtual int setMode(SPI_MODE mode);
	virtual int setBitsPerWord(uint8_t bits);

private:
	int file;
	std::string filename;
	uint8_t bits;
	uint32_t speed;
	uint16_t delay;
	SPI_MODE mode;

	int transfer(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t num);

};

} /* namespace BBB */

#endif /* __SPI__ */