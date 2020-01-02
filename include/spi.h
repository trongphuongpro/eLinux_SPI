#ifndef __SPI__
#define __SPI__

#define SPI_PATH	"/dev/spidev"

namespace BBB {

class SPI {
public:
	enum MODE {MODE0=0, MODE1, MODE2, MODE3};
	enum ORDER {MSB=0, LSB=1};
	enum BUS {SPI0=1, SPI1=2};

	SPI(BUS bus);
	~SPI();

	virtual int open();
	virtual void close();

	virtual int read();
	virtual int read(uint8_t reg);
	virtual int readBuffer(void *buffer, uint16_t num);
	virtual int readBuffer(uint8_t reg, void *buffer, uint16_t num);

	virtual int write(uint8_t value);
	virtual int write(uint8_t reg, uint8_t value);
	virtual int writeBuffer(const void *buffer, uint16_t num);
	virtual int writeBuffer(uint8_t reg, const void *buffer, uint16_t num);

	virtual int setSpeed(uint32_t speed);
	virtual int setMode(MODE mode);
	virtual int setBitsPerWord(uint8_t bits);
	virtual int setBitOrder(ORDER);

private:
	int file;
	std::string filename;
	uint8_t bits;
	uint32_t speed;
	uint16_t delay;
	MODE mode;
	ORDER bitOrder;

	int transfer(const uint8_t *txBuffer, const uint8_t *rxBuffer, uint16_t num);

};

} /* namespace BBB */

#endif /* __SPI__ */