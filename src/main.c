#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// ----- State Machine -----
typedef enum {
    SENSOR_INIT,
    SENSOR_READ,
    SENSOR_PROCESS
} SensorState;

static uint16_t mock_adc_value = 0;

// ----- Mock ADC function -----
uint16_t read_adc_sensor() {
    // Simulating ADC changing values
    mock_adc_value = (mock_adc_value + (rand() % 50)) % 1024;
    return mock_adc_value;
}

// ----- Processing Function -----
float convert_to_voltage(uint16_t adc_value) {
    // 10-bit ADC, 0–1023 mapped to 0–5V
    return (adc_value * 5.0f) / 1023.0f;
}

int main(void) {
    srand(time(NULL));
    SensorState state = SENSOR_INIT;

    for (int i = 0; i < 10; i++) {

        switch (state) {
            case SENSOR_INIT:
                printf("[INIT] Sensor initialized.\n");
                state = SENSOR_READ;
                break;

            case SENSOR_READ: {
                uint16_t val = read_adc_sensor();
                printf("[READ] Raw ADC: %u\n", val);
                state = SENSOR_PROCESS;
                break;
            }

            case SENSOR_PROCESS: {
                float voltage = convert_to_voltage(mock_adc_value);
                printf("[PROCESS] Voltage: %.2f V\n", voltage);
                state = SENSOR_READ; // loop back
                break;
            }
        }
    }

    return 0;
}