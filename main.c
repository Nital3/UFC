#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"

#include "ssi.h"
#include "cgi.h"

//WIFI Creds
const char WIFI_SSID[] = "HUAWEI";
const char WIFI_PSWD[] = "10101010";


int main(){

    stdio_init_all();
    cyw43_arch_init();
    cyw43_arch_enable_sta_mode();

    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PSWD, CYW43_AUTH_WPA2_AES_PSK, 30000))
    {
        printf("Connecting...");
    }
        printf("Connected!");

    //Initialise html server
    httpd_init();


    ssi_init();
    cgi_init();
    

    for(;;);

}
