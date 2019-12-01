#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "spi.h"


using namespace BBB;
using namespace std;


SPI::SPI(BUS bus) {
	this->filename = SPI_PATH + to_string(bus) + ".0";
	this->mode = MODE3;
	this->bits = 8;
	this->bitOrder = MSB;
	this->speed = 500000;
	this->delay = 0;
	this->open();
}


SPI::~SPI() {
	if (this->file != -1)
		close();
}


int SPI::open() {
	if ((this->file = ::open(this->filename.c_str(), O_RDWR)) < 0) {
		perror("Fail to open SPI bus");
		return -1;
	}
	if (this->setMode(this->mode) == -1) {
		perror("SPI: fail to set SPI bus mode");
		return -1;
	}
	if (this->setSpeed(this->speed) == -1) {
		perror("SPI: fail to set SPI bus speed");
		return -1;
	}
	if (this->setBitsPerWord(this->bits) == -1) {
		perror("SPI: fail to set SPI bus bits/Word");
		return -1;
	}
	if (this->setBitOrder(this->bitOrder) == -1) {
		perror("SPI: fail to set SPI bus bit order");
		return -1;
	}
	return 0;
}


void SPI::close() {
	::close(this->file);
	this->file = -1;
}


int SPI::transfer(uint8_t *txBuffer, uint8_t *rxBuffer, uint16_t num) {
	struct spi_ioc_transfer transfer;
	memset(&transfer, 0, sizeof(transfer));

	transfer.tx_buf = (uintptr_t)txBuffer;
	transfer.rx_buf = (uintptr_t)rxBuffer;
	transfer.len = num;
	transfer.speed_hz = this->speed;
	transfer.bits_per_word = this->bits;
	transfer.delay_usecs = this->delay;
	transfer.tx_nbits = 0;
	transfer.rx_nbits = 0;
	transfer.cs_change = 0;
	transfer.pad = 0;

	int status = ioctl(this->file, SPI_IOC_MESSAGE(1), &transfer);
	if (status < 0) {
		perror("SPI: SPI_IOC_MESSAGE failed");
		return -1;
	}
	return status;
}


uint8_t SPI::read() {
	uint8_t rxValue = 0, txValue = 0;

	if (transfer(&txValue, &rxValue, 1) == -1) {
		perror("SPI: read failed");
		return 0xFF;
	}

	return rxValue;
}


uint8_t SPI::read(uint8_t reg) {
	uint8_t txBuffer[2] = {0};
	uint8_t rxBuffer[2] = {0};

	txBuffer[0] = reg;

	if (transfer(txBuffer, rxBuffer, 2) == -1) {
		perror("SPI: read failed");
		return 0xFF;
	}

	return rxBuffer[1];
}


int SPI::readBuffer(void *rxBuffer, uint16_t num) {
	uint8_t txBuffer[num] = {0};
	uint8_t *__rxBuffer = (uint8_t*)rxBuffer;

	if (transfer(txBuffer, __rxBuffer, num) == -1) {
		perror("SPI: read buffer failed");
		return -1;
	}
	return 0;
}


int SPI::readBuffer(uint8_t reg, void* rxBuffer, uint16_t num) {
	uint8_t txBuffer[num] = {0};
	uint8_t *__rxBuffer = (uint8_t*)rxBuffer;

	if (transfer(&reg, NULL, 1) == -1) {
		perror("SPI: set address failed");
		return -1;
	}

	if (transfer(txBuffer, __rxBuffer, num) == -1) {
		perror("SPI: read buffer failed");
		return -1;
	}

	return 0;
}


int SPI::write(uint8_t value) {
	if (transfer(&value, NULL, 1) == -1) {
		perror("SPI: write failed");
		return -1;
	}
	return 0;
}


int SPI::write(uint8_t reg, uint8_t value) {
	uint8_t txBuffer[2] = {reg, value};

	if (transfer(txBuffer, NULL, 2) == -1) {
		perror("SPI: write failed");
		return -1;
	}
	return 0;
}


int SPI::writeBuffer(void *buffer, uint16_t num) {
	uint8_t *__buffer = (uint8_t*)buffer;

	if (transfer(__buffer, NULL, num) == -1) {
		perror("SPI: write buffer failed");
		return -1;
	}
	return 0;
}


int SPI::writeBuffer(uint8_t reg, void *buffer, uint16_t num) {
	uint8_t *__buffer = (uint8_t*)buffer;

	if (transfer(&reg, NULL, 1) == -1) {
		perror("SPI: set address failed");
		return -1;
	}

	if (transfer(__buffer, NULL, num) == -1) {
		perror("SPI: write buffer failed");
		return -1;
	}
	return 0;
}


int SPI::setSpeed(uint32_t speed) {
	this->speed = speed;
	if (ioctl(this->file, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed) == -1) {
		perror("SPI: cannot set max speed Hz");
		return -1;
	}
	if (ioctl(this->file, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed) == -1) {
		perror("SPI: cannot set max speed Hz");
		return -1;
	}
	return 0;
}


int SPI::setMode(MODE mode) {
	this->mode = mode;
	if (ioctl(this->file, SPI_IOC_WR_MODE, &this->mode) == -1){
		perror("SPI: cannot set SPI mode.");
		return -1;
	}
	if (ioctl(this->file, SPI_IOC_RD_MODE, &this->mode) == -1){
		perror("SPI: cannot set SPI mode.");
		return -1;
	}
	return 0;
}


int SPI::setBitsPerWord(uint8_t bits) {
	this->bits = bits;
	if (ioctl(this->file, SPI_IOC_WR_BITS_PER_WORD, &this->bits) == -1){
		perror("SPI: cannot set bits per word.");
		return -1;
	}
	if (ioctl(this->file, SPI_IOC_RD_BITS_PER_WORD, &this->bits) == -1){
		perror("SPI: cannot set bits per word.");
		return -1;
	}
	return 0;
}


int SPI::setBitOrder(ORDER order) {
	this->bitOrder = order;
	if (ioctl(this->file, SPI_IOC_WR_LSB_FIRST, &this->bitOrder) == -1){
		perror("SPI: cannot set bit order");
		return -1;
	}
	if (ioctl(this->file, SPI_IOC_RD_LSB_FIRST, &this->bitOrder) == -1){
		perror("SPI: cannot set bit order.");
		return -1;
	}
	return 0;
}