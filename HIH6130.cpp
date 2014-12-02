/*
  HIH6130.cpp - Library for reading RHT data from the Honeywell HIH6130.
  Created by David H Hagan, November 22, 2014.
  
  Use as you like. MIT license.
*/

#include "Arduino.h"
#include "HIH6130.h"
#include <Wire.h>

HIH6130::HIH6130(uint8_t address)
{
	_address = address;
	_humidity_lo = 0;
	_humidity_hi = 0;
	_humidity_data = 0;
	_temp_data = 0;
	_temp_hi = 0;
	_temp_lo = 0;
	_status = 0;
}

void HIH6130::begin(){
	
	// setup the HIH6130 sensor
	Wire.begin();
}

void HIH6130::readRHT(){

	// reads data from the sensor and stores them in temporary variables that
	// are then accessed via the readT() and readRH functions
	Wire.beginTransmission(_address);
	Wire.endTransmission();

	Wire.requestFrom( (int) _address, (int) 4);
	while (Wire.available() == 0);

	_humidity_hi = Wire.read();
	_humidity_lo = Wire.read();
	_temp_hi = Wire.read();
	_temp_lo = Wire.read();

	Wire.endTransmission();

	// Get the status (first two bits of _humidity_hi_)
	_status = (_humidity_hi >> 6);

	// Drop the first two bits from _humidity_hi
	_humidity_hi = _humidity_hi & 0x3f;

	// Add the two 8-bit registers together -> relative humidity
	_humidity_data = ((unsigned int) _humidity_hi << 8) | _humidity_lo;

	// Add the two 8-bit registers together -> temperature
	_temp_data = (unsigned int) (_temp_hi << 6) + (_temp_lo >> 2);

	//humidity = 2.3;
	//temperature = 1.0;
	humidity = (double) _humidity_data * 100 / (pow(2,14) - 1);
	temperature = (double) (_temp_data / (pow(2,14) - 1)) * 165 - 40;
}