#ifndef __ADC_H
#define __ADC_H

#define EMPTY_BYTE		0x00
#define VOLTAGE_A 		0x4B
#define VOLTAGE_B 		0x4D
#define VOLTAGE_C 		0x4F
#define SETTINGS			0x59
#define NUM_VOLTAGE		3
#define PRECISION			40

#include <stdbool.h> 
#include <stdint.h>


void Read_Voltage(uint16_t request, int32_t *data);
void Calculate_Sign(int32_t *data);
void Convert_Data(int32_t *data, double *data_d);
void Calculate_Value(double g_data[][NUM_VOLTAGE], double *voltage);
void Read_Array(int32_t (*g_buffer)[NUM_VOLTAGE], int count);
void ADC_MCP3914_Init();
void Voltage_Measurement(double *voltage);
void Delay(unsigned long p);

#endif // __ADC_H 