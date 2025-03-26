#ifndef HX711_H
#define HX711_H

#include <stdint.h>
#include <stdbool.h>

#include "hx711_hw.h"

#define NUMBER_OF_RETRY 100

typedef enum
{
    HX711_FAIL,          // operation fails
    HX711_SUCCESS,       // oeration success
    HX711_TIMEOUT,       // operation timeout
    HX711_INVALID_PARAM, // invalid input params
} errno_t;

typedef enum
{
    HX711_SP_10HZ,
    HX711_SP_80HZ,
} hx711_sampling_rate_e;

typedef enum
{
    HX711_GAIN_128 = 1,
    // HX711_GAIN_32 = 2, // this is for chan B, not supported
    HX711_GAIN_64 = 3
} hx711_gain_e;

typedef struct
{
    hx711_gain_e gain;
    hx711_sampling_rate_e sampling_rate;
    float base_weight;       // y0
    uint32_t base_raw_value; // x0
    float ref_weight;        // y1
    uint32_t ref_raw_value;  // x1
    float coef;              // a
    float offset;            // b
} hx711_calib_val_t;

/*=========================SETUP====================*/
errno_t hx711_init(hx711_gain_e gain, bool set_base,
                   float base_weight, uint32_t base_raw_value);
errno_t hx711_set_gain(hx711_gain_e gain);
errno_t hx711_tare(void);
errno_t hx711_set_ref_weight(uint32_t weight, uint32_t raw_value);

/*=================================================*/
/**
 * @brief  Get raw data from HX711
 * @return 32bit raw data
 */
uint32_t hx711_get_data_raw(void);

float hx711_get_weight(void);

/*=================================================*/
errno_t hx711_enter_power_down(void);

#endif // HX711_H