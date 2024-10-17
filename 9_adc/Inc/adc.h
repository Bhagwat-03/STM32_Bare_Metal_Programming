/*
 * adc.h
 *
 *  Created on: Oct 15, 2024
 *      Author: Admin
 */

#ifndef ADC_H_
#define ADC_H_


#include <stdint.h>
void adc_converter(void);
void start_conversion(void);
uint32_t adc_read();


#endif /* ADC_H_ */
