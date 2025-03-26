
#include "main.h"
#include "hal_tim.h"
#include "hal_usart.h"
#include "hal_gpio.h"
#include "hal_utils.h"
#include "syscfg.h"

#include "hx711.h"

#define ENTER_POWER_DOWN_MODE

/* Link the STM32 HAL to hx711 operations*/
static void hx711_com_init(void)
{
  hx711_hw_ops_t hx711_hw_ops = {
      .write_sck = hal_gpio_hx711_write_sck,
      .read_dat = hal_gpio_hx711_read_dat,
      .delay_us = hal_tim_busy_wait_us,
  };
  hx711_set_hw_ops(&hx711_hw_ops);
}

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM2_Init();
  HAL_TIM_Base_Start(&htim2);
  MX_USART1_UART_Init();

  hx711_com_init();
  hx711_init(HX711_GAIN_128, false, 0, 0);

  float data = 0;
  char data_str[20];

  while (1)
  {
    HAL_GPIO_TogglePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
    HAL_Delay(1000);
    data = hx711_get_weight();
    if (data)
    {
      hal_utils_float_to_str(data, data_str, 5);
      hal_uart_printf("Weight: %s(g)\n", data_str);
#ifdef ENTER_POWER_DOWN_MODE
      hx711_enter_power_down();
      while (1)
        ;
#endif
    }
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
