#include "pico/stdlib.h"
#include "functions.h"
#include <math.h>

double calculate_voltage(uint16_t adc_value){
    return((33.0 * adc_value) / ((1<<12)*10));
}

double calculate_resistance(double voltage){

    //ADC_read_voltage * Resistor_value / Input_voltage - ADC_read_voltahe
    return(((33.0*(10000/10))/voltage)-10000);


}


float calculate_temperature(double resistance){

    //Calculates Temperature using Steinhart-Hart equation

    //Coefficients for "SRpassives NTCC-10K" Thermistor
    const long double A = 0.001194595408;
    const long double B = 0.0002271649836;
    const long double C = 0.00000008595005957;

    //Calculate temperature in Kelvin
    long double TempK = 1/(A + (B * log(resistance)) + C * pow(log(resistance),3.0f));

    //Convert to Celsius
    long double TempC = TempK - 273.15f;

    return(TempC);


}

