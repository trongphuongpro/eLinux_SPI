/**
 * @file spi.h
 * @brief Wrapper class for SPI communication (only in master) in eLinux.
 * @author Nguyen Trong Phuong (aka trongphuongpro)
 * @date 2020 Jan 22.
 */

#ifndef __SPI__
#define __SPI__

#define SPI_PATH	"/dev/spidev"

namespace BBB {


/**
 * @brief Wrapper class containing functions for SPI communication.
 */ 
class SPI {
public:

	/**
	 * @brief Data mode: mode 0, mode 1, mode 2 and mode 3.
	 */
	enum DATAMODE {MODE0=0, MODE1, MODE2, MODE3};


	/**
	 * @brief Trasmittion bit order: MSB or LSB
	 */
	enum BITORDER {MSB=0, LSB=1};


	/**
	 * @brief SPI bus: SPI0 or SPI1.
	 */
	enum BUS {SPI0=1, SPI1=2};


	/**
	 * @brief Constructor
	 * 
	 * Initialize SPI bus with default settings: 8-bit data, MSB First, Mode 0.
	 * @param bus SPI0 or SPI1.
	 * @param speed speed for SPI transmitting, e.x. 500000.
	 */
	SPI(BUS bus, uint32_t speed);

	/**
	 * @brief Destructor
	 */
	~SPI();


	/**
	 * @brief Read 1 byte from SPI bus.
	 * @return one byte.
	 */
	virtual int read();


	/**
	 * @brief Read 1 byte from a specific register via SPI bus.
	 * @param reg register that will be read.
	 * @return one byte.
	 */
	virtual int read(uint8_t reg);


	/**
	 * @brief Read 1 array from SPI bus.
	 * @param buffer pointer to array.
	 * @param len the length of data array.
	 * @return 0:success, -1:failed.
	 */
	virtual int readBuffer(void *buffer, uint32_t len);


	/**
	 * @brief Read 1 array from a specific register via SPI bus.
	 * @param reg register that will be read.
	 * @param buffer pointer to array.
	 * @param len the length of data array.
	 * @return 0:success, -1:failed.
	 */
	virtual int readBuffer(uint8_t reg, void *buffer, uint32_t len);


	/**
	 * @brief Write 1 byte to SPI bus.
	 * @param value data that will be sent.
	 * @return 0:success, -1:failed.
	 */
	virtual int write(uint8_t value);


	/**
	 * @brief Write 1 byte to a specific register via SPI bus.
	 * @param reg register that will be written.
	 * @param value data that will be sent.
	 * @return 0:success, -1:failed.
	 */
	virtual int write(uint8_t reg, uint8_t value);


	/**
	 * @brief Write 1 array to SPI bus.
	 * @param buffer pointer to data array that will be sent.
	 * @param len the length of data array.
	 * @return 0:success, -1:failed.
	 */
	virtual int writeBuffer(const void *buffer, uint32_t len);


	/**
	 * @brief Write 1 array to a specific register via SPI bus.
	 * @param reg register that will be written.
	 * @param buffer pointer to data array that will be sent.
	 * @param len the length of data array.
	 * @return 0:success, -1:failed.
	 */
	virtual int writeBuffer(uint8_t reg, const void *buffer, uint32_t len);


	/**
	 * @brief Set speed for SPI transmitting.
	 * @param speed Transmitting speed, e.x. 500000.
	 * @return 0:success, -1:failed.
	 */
	virtual int setSpeed(uint32_t speed);


	/**
	 * @brief Set data mode for SPI transmitting.
	 * @param mode MODE0, MODE1, MODE2 or MODE3.
	 * @return 0:success, -1:failed.
	 */
	virtual int setDataMode(DATAMODE mode);


	/**
	 * @brief Set data size for SPI transmitting.
	 * @param bits data size.
	 * @return 0:success, -1:failed.
	 */
	virtual int setBitsPerWord(uint8_t bits);


	/**
	 * @brief Set bit order for SPI transmitting.
	 * @param order MSB or LSB.
	 * @return 0: success, -1: failed.
	 */
	virtual int setBitOrder(BITORDER order);

private:
	int file;
	std::string filename;
	uint8_t bits;
	uint32_t speed;
	uint16_t delay;
	DATAMODE mode;
	BITORDER bitOrder;

	int open();
	void close();

	int transfer(const void *txBuffer, void *rxBuffer, uint32_t num);

};

} /* namespace BBB */

#endif /* __SPI__ */