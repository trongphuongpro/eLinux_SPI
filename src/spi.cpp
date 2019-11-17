#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include "spi.h"


using namespace BBB;
using namespace std;


SPI::SPI(SPI_BUS bus) {
	this->filename = SPI_PATH + to_string(bus) + ".0";
	this->mode = MODE3;
	this->bits = 8;
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
	/*if (this->setMode(this->mode) == -1) {
		perror("Fail to set SPI bus mode");
		return -1;
	}
	if (this->setSpeed(this->speed) == -1) {
		perror("Fail to set SPI bus speed");
		return -1;
	}
	if (this->setBitsPerWord(this->bits) == -1) {
		perror("Fail to set SPI bus bits/Word");
		return -1;
	}*/
	return 0;
}


void SPI::close() {
	::close(this->file);
	this->file = -1;
}