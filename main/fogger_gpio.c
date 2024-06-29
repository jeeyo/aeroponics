#include "aeroponics.h"

#include "esp_log.h"
#include "driver/gpio.h"

static const char *TAG = "FOGGER";

int fogger_init(fogger_t *fogger, int gpio)
{
  gpio_config_t io_conf = {
    .intr_type = GPIO_INTR_DISABLE,
    .mode = GPIO_MODE_OUTPUT,
    .pin_bit_mask = 1ULL << gpio,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .pull_up_en = GPIO_PULLUP_ENABLE  // active low
  };

  esp_err_t result = gpio_config(&io_conf);
  if (result != ESP_OK) {
    return -1;
  }

  fogger->gpio = gpio;
  ESP_LOGI(TAG, "A fogger device initialized on GPIO%d", gpio);

  fogger_write(&fogger, 1); // turn fogger on
  return 0;
}

void fogger_write(fogger_t *fogger, int onoff)
{
  // active low
  gpio_set_level(fogger->gpio, onoff ? 0 : 1);
}
