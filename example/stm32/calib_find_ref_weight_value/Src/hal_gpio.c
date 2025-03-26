
#include "hal_gpio.h"
#include "main.h"

void MX_GPIO_Init(void)
{
  /* GPIO Ports Clock Enable */
  hal_gpio_builtin_led_init();
  hal_gpio_hx711_dat_init();
  hal_gpio_hx711_sck_init();
}

void hal_gpio_builtin_led_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOC_CLK_ENABLE();
  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = BUILTIN_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUILTIN_LED_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BUILTIN_LED_PORT, BUILTIN_LED_PIN, GPIO_PIN_RESET);
}

void hal_gpio_builtin_led_deinit(void)
{
  HAL_GPIO_DeInit(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
}

/*=======================================================================*/

void hal_gpio_hx711_dat_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Pin = HX711_DT_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(HX711_DT_PORT, &GPIO_InitStruct);
}

void hal_gpio_hx711_dat_deinit(void)
{
  HAL_GPIO_DeInit(BUILTIN_LED_PORT, BUILTIN_LED_PIN);
}

void hal_gpio_hx711_sck_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIOB_CLK_ENABLE();
  /*Configure GPIO pin : PB9 */
  GPIO_InitStruct.Pin = HX711_SCK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(HX711_SCK_PORT, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HX711_SCK_PORT, HX711_SCK_PIN, GPIO_PIN_RESET);
}

void hal_gpio_hx711_sck_deinit(void)
{
  HAL_GPIO_DeInit(HX711_SCK_PORT, HX711_SCK_PIN);
}

int hal_gpio_hx711_write_sck(int val)
{
  HAL_GPIO_WritePin(HX711_SCK_PORT, HX711_SCK_PIN, val);
  return 0;
}

int hal_gpio_hx711_read_dat(void)
{
  return HAL_GPIO_ReadPin(HX711_DT_PORT, HX711_DT_PIN);
}