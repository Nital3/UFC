#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"


#ifndef SSI_H
#define SSi_H


u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);
void ssi_init();

#endif