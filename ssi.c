#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"
#include "functions.h"

#include "ssi.h"

//Set SSI tags
const char * ssi_tags[] = {"volt","temp","res","adc"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen){
    size_t printed;

    switch ((iIndex))
    {
        case 0: //voltage
        {
            
            float voltage = calculate_voltage(adc_read());
            printed = snprintf(pcInsert, iInsertLen, "%.2f", voltage);

        }
        break;




        case 1: //temp
        {

            float temperature = calculate_temperature(calculate_resistance(calculate_voltage(adc_read())));
            printed = snprintf(pcInsert, iInsertLen, "%.2f", temperature);
            
        }
        break;


        case 2: //Resistance
        {

            float resistance = calculate_resistance(calculate_voltage(adc_read()));
            printed = snprintf(pcInsert, iInsertLen, "%.2f", resistance);
            
        }
        break;
    
        case 3: //ADC
        {

            
            printed = snprintf(pcInsert, iInsertLen, "%i", adc_read());
            
        }
        break;

        default:
        {
        printed = 0;
        break;
        }
    }

return(u16_t)printed;

}



void ssi_init(){
    //initialise adc
    adc_init();
    adc_select_input(0);


    //configure SSI handler
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}