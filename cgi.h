#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"


#ifndef CGI_H
#define CGI_H

const char * cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);
void cgi_init(void);

#endif