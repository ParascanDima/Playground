/*
 * mrf24j40.c
 *
 *  Created on: Feb 7, 2017
 *      Author: Andrei
 */

#include "HAL/avr-hal/SPI/avr-spi.h"

#include <stdint.h>

#define MRF24J40_BUFF_SIZE 32

uint8_t MRF24J4_Buff[32]; // address resolver


uint8_t MRF24J40_TansferCommplette(void){
 return SPI_buffer_transfer_commplette();
}


int16_t MRF24J40_Write(uint16_t addr, uint8_t * buff, int16_t size) {


	uint8_t addrSize;

	if (addr <= (0x3F)){ //
		addrSize = 1;
	    MRF24J4_Buff[0] = addr << 1; // set address
	    MRF24J4_Buff[0] &=~(0x80);   // 0 - short address
	    MRF24J4_Buff[0] |= (0x01);   // 1 - write
	}
	else if (addr >= (0x200) && addr<=0x38F){
		addrSize = 2;
	    MRF24J4_Buff[0] = addr >> 3 ;    // set address
	    MRF24J4_Buff[1] = addr << 5;    // set address
	    MRF24J4_Buff[0] |= (0x80);      // 0 - long address
	    MRF24J4_Buff[1] |= (0x01) << 4; // 1 - write
	}
	else
		return -1;

	BuffCpi(buff, MRF24J4_Buff + addrSize, size);

	SPI_TransferBuf(MRF24J4_Buff, 0, addrSize + size);

	return 0;
}

int16_t MRF24J40_Read(uint16_t addr, uint8_t * buff, int16_t size) {


	uint8_t addrSize;

	if (addr <= (0x3F)){ //
		addrSize = 1;
	    MRF24J4_Buff[0] = addr << 1; // set address
	    MRF24J4_Buff[0] &=~(0x80);   // 0 - short address
	    MRF24J4_Buff[0] &=~(0x01);   // 0 - read
	}
	else if (addr >= (0x200) && addr<=0x38F){
		addrSize = 2;
	    MRF24J4_Buff[0] = addr >> 3 ;   // set address
	    MRF24J4_Buff[1] = addr << 5;    // set address
	    MRF24J4_Buff[0] |= (0x80);      // 0 - long address
	    MRF24J4_Buff[1] &=~(0x01) << 4; // 0 - read
	}
	else
		return -1;

	BuffClr(MRF24J4_Buff + addrSize, size);

	SPI_TransferBuf(MRF24J4_Buff, buff, addrSize + size);

	return 0;
}
