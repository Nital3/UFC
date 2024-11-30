#include "pico/stdlib.h"

double calculate_voltage(uint16_t adc_value);
double calculate_resistance(double voltage);
float calculate_temperature(double resistance);