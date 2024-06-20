#include "aeroponics.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_check.h"
#include "dht.h"

static const char *TAG = "DHT11";

int temphumid_init(temphumid_t *temphumid, int gpio)
{
  temphumid->gpio = gpio;
  ESP_LOGI(TAG, "A DHT11 device initialized on GPIO%d", gpio);
  return 0;
}

int temphumid_read(temphumid_t *temphumid, float *temperature, float *humidity)
{
  return dht_read_float_data(DHT_TYPE_DHT11, temphumid->gpio, humidity, temperature) == ESP_OK ? 0 : -1;
}
