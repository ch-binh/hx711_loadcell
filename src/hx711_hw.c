#include "hx711_hw.h"

static hx711_hw_ops_t hx711_hw_ops;

void hx711_set_hw_ops(hx711_hw_ops_t *ops)
{
    hx711_hw_ops = *ops;
}

int hx711_write_clk(int val)
{
    if (hx711_hw_ops.write_sck)
    {
        hx711_hw_ops.write_sck(val);
        return 0;
    }
    return -1;
}

int hx711_read_dat(void)
{
    if (hx711_hw_ops.read_dat)
    {
        return hx711_hw_ops.read_dat();
    }
    return -1;
}

int hx711_us_delay(int us)
{
    if (hx711_hw_ops.delay_us)
    {
        hx711_hw_ops.delay_us(us);
        return 0;
    }
    return -1;
}