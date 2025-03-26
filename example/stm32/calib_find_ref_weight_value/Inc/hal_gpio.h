
#ifndef __GPIO_H__
#define __GPIO_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

typedef enum
{
  PIN_MODE_INPUT,
  PIN_MODE_OUTPUT
} pin_mode_e;

#define LOW 0
#define HIGH 1

void MX_GPIO_Init(void);

void hal_gpio_builtin_led_init(void);
void hal_gpio_builtin_led_deinit(void);

/*=======================================================================*/

void hal_gpio_hx711_dat_init(void);
void hal_gpio_hx711_dat_deinit(void);

void hal_gpio_hx711_sck_init(void);
void hal_gpio_hx711_sck_deinit(void);

int hal_gpio_hx711_write_sck(int val);
int hal_gpio_hx711_read_dat(void);

#endif /*__ GPIO_H__ */
