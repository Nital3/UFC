#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"


#define GPIO_ON 1
#define GPIO_OFF 0
#define PWM_GPIO_PIN 0
#define PULL_UP_PIN 15
#define BUTTON_GPIO_PIN 16


int main(){

    //Initialize wifi module and turn on LED to indicate program is loaded and working
    cyw43_arch_init();
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, GPIO_ON);


    //Set GPIO 14 pin to PWM mode
    gpio_set_function(PWM_GPIO_PIN, GPIO_FUNC_PWM);

    //Get PWM channel for that pin;
    uint slice_number = pwm_gpio_to_slice_num(PWM_GPIO_PIN);

    //Turn PWM on
    pwm_set_enabled(slice_number, true);

    //Set the PWM wrap point for 2kHz
    int pwm_wrap_point = 62500;
    pwm_set_wrap(slice_number, pwm_wrap_point);


    //Mode_button setup
    stdio_init_all();
    gpio_init(BUTTON_GPIO_PIN);
    gpio_set_dir(BUTTON_GPIO_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO_PIN);

    //Test tacho pin
    gpio_pull_up(PULL_UP_PIN);

    int mode = 0;

    for(;;){


        while (gpio_get(BUTTON_GPIO_PIN)){

            switch (mode){

            case 0: //Brightness 0%
                pwm_set_chan_level(slice_number, PWM_CHAN_A, 0);
                break;

            case 1: //Brightness 25%
                pwm_set_chan_level(slice_number, PWM_CHAN_A, pwm_wrap_point*0.25f);
                break;

            case 2: //Brightness 50%
                pwm_set_chan_level(slice_number, PWM_CHAN_A, pwm_wrap_point*0.5f);
                break;

            case 3: //Brightness 100%
                pwm_set_chan_level(slice_number, PWM_CHAN_A, pwm_wrap_point);
                break;

            default:
                break;

            }

        }
        
        if(mode<3){
            mode++;
        }
        else{
            mode = 0;
        }

        sleep_ms(250);


    }

}
