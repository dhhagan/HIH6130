/*
	Example showing how to use the HIH6130 library for Arduino

	Written by David Hagan, December 2, 2014
*/

#include <"HIH6130.h">

HIH6130 rht(0x27);

void setup(){
	Serial.begin(9600);

	rht.begin();
}

void loop(){
	rht.hello();

	delay(2000);
}