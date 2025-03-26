#ifndef HX711_HW_H
#define HX711_HW_H

typedef struct
{
    int (*write_sck)(int val);
    int (*read_dat)(void);
    int (*delay_us)(int us);
} hx711_hw_ops_t;

void hx711_set_hw_ops(hx711_hw_ops_t *ops);

int hx711_write_clk(int val);
int hx711_read_dat(void);
int hx711_us_delay(int us);

#endif // HX711_HW_H