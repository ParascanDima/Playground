/*
 * mrf24j40.h
 *
 *  Created on: Feb 7, 2017
 *      Author: Andrei
 */

#ifndef BSW_COM_MRF24J40_SRC_MRF24J40_H_
#define BSW_COM_MRF24J40_SRC_MRF24J40_H_


#include "mrf24j40_cfg.h"


int16_t MRF24J40_Write(uint16_t addr, uint8_t * buff, int16_t size);
int16_t MRF24J40_Read(uint16_t addr, uint8_t * buff, int16_t size);
uint8_t MRF24J40_TansferCommplette(void);

#endif /* BSW_COM_MRF24J40_SRC_MRF24J40_H_ */
