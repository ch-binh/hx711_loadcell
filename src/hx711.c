#include "hx711.h"

static hx711_calib_val_t _calib_val = {
    .gain = HX711_GAIN_128,
    .sampling_rate = HX711_SP_10HZ,
    .base_weight = 0.0,
    .ref_weight = 188.0,
    .ref_raw_value = 7793115,

};
/*=========================SETUP====================*/
//
errno_t hx711_init(hx711_gain_e gain, bool set_base,
                   float base_weight, uint32_t base_raw_value)
{
    errno_t err;
    hx711_set_gain(gain);

    err = hx711_tare();
    if (err == HX711_FAIL)
        return err;

    if (set_base)
    {
        _calib_val.base_weight = base_weight;
        _calib_val.base_raw_value = base_raw_value;
    }

    _calib_val.coef = (float)_calib_val.ref_weight /
                      (int)(_calib_val.ref_raw_value - _calib_val.base_raw_value);

    _calib_val.offset = _calib_val.base_weight -
                        _calib_val.coef * _calib_val.base_raw_value;

    return HX711_SUCCESS;
}

errno_t hx711_set_gain(hx711_gain_e gain)
{
    _calib_val.gain = gain;
    return HX711_SUCCESS;
}

// calibrate function
errno_t hx711_tare(void)
{
    uint32_t value = 0;
    for (int i = 0; i < NUMBER_OF_RETRY; i++)
    {
        value = hx711_get_data_raw();
        if (value)
        {
            _calib_val.base_raw_value = value;
            return HX711_SUCCESS;
        }
        hx711_us_delay(10000);
    }
    return HX711_TIMEOUT;
}

errno_t hx711_set_ref_weight(uint32_t weight, uint32_t raw_value)
{
    _calib_val.ref_weight = weight;

    if (raw_value)
    {
        _calib_val.ref_raw_value = raw_value;
        return HX711_SUCCESS;
    }

    // if raw_value not specified, get it from HX711
    uint32_t value = 0;
    for (int i = 0; i < NUMBER_OF_RETRY; i++)
    {
        value = hx711_get_data_raw();
        if (value)
        {
            _calib_val.ref_raw_value = value;
            return HX711_SUCCESS;
        }
        hx711_us_delay(10000);
    }
    return HX711_TIMEOUT;
}

/*=======================================================*/

uint32_t hx711_get_data_raw(void)
{
    // check if data is ready or not
    if (hx711_read_dat())
        return 0;

    uint32_t data = 0;
    // read data
    for (int8_t len = 0; len < 24; len++)
    {
        hx711_write_clk(1);
        hx711_us_delay(10);
        data = data << 1;
        hx711_write_clk(0);
        hx711_us_delay(10);
        if (hx711_read_dat())
            data++;
    }
    data = data ^ 0x800000;
    // set gain
    for (int i = 0; i < _calib_val.gain; i++)
    {
        hx711_write_clk(1);
        hx711_us_delay(10);
        hx711_write_clk(0);
        hx711_us_delay(10);
    }
    return data;
}

float hx711_get_weight(void)
{
    uint32_t data = hx711_get_data_raw();
    if (!data)
        return 0;
    return (_calib_val.coef * (float)data + _calib_val.offset);
}

/*=======================================================*/

errno_t hx711_enter_power_down(void)
{
    hx711_write_clk(1);
    return HX711_SUCCESS;
}
