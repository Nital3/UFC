#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

#include "ssi.h"

//Set SSI tags
const char * ssi_tags[] = {"temp"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen){
    size_t printed;

    switch ((iIndex))
    {
    case 0: //temp
        {
            const float voltage = adc_read() * 3.3f / (1<<12);
            const float tempC = 27.0f - (voltage - 0.706f) / 0.001721f;
            printed = snprintf(pcInsert, iInsertLen, "%f", tempC);
            
        }
        break;
    
    default:
        printed = 0;
        break;
    }

return(u16_t)printed;

}



void ssi_init(){
    //initialise adc
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);


    //configure SSI handler
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}