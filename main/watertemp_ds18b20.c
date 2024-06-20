#include "aeroponics.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_check.h"
#include "onewire_bus.h"
#include "ds18b20.h"

static const char *TAG = "WATERTEMP";

int watertemp_init(watertemp_t *watertemp, int gpio)
{
  // install new 1-wire bus
  onewire_bus_handle_t bus;
  onewire_bus_config_t bus_config = {
    .bus_gpio_num = gpio,
  };
  onewire_bus_rmt_config_t rmt_config = {
    .max_rx_bytes = 10, // 1byte ROM command + 8byte ROM number + 1byte device command
  };
  ESP_ERROR_CHECK(onewire_new_bus_rmt(&bus_config, &rmt_config, &bus));
  ESP_LOGI(TAG, "1-Wire bus installed on GPIO%d", gpio);

  onewire_device_iter_handle_t iter = NULL;
  esp_err_t search_result = ESP_OK;

  // create 1-wire device iterator, which is used for device search
  ESP_ERROR_CHECK(onewire_new_device_iter(bus, &iter));
  ESP_LOGI(TAG, "Device iterator created, start searching...");

  do
  {
    search_result = onewire_device_iter_get_next(iter, &watertemp->onewire_device);
    if (search_result == ESP_OK)
    { // found a new device, let's check if we can upgrade it to a DS18B20
      ds18b20_config_t ds_cfg = {};
      if (ds18b20_new_device(&watertemp->onewire_device, &ds_cfg, &watertemp->ds18b20) == ESP_OK)
      {
        ESP_LOGI(TAG, "Found a DS18B20, address: %016llX", watertemp->onewire_device.address);
        break;
      }
      else
      {
        ESP_LOGI(TAG, "Found an unknown device, address: %016llX", watertemp->onewire_device.address);
      }
    }
  } while (search_result != ESP_ERR_NOT_FOUND);

  ESP_ERROR_CHECK(onewire_del_device_iter(iter));
  ESP_LOGI(TAG, "Searching done");

  // set resolution
  ESP_ERROR_CHECK(ds18b20_set_resolution(watertemp->ds18b20, DS18B20_RESOLUTION_12B));
  return 0;
}

int watertemp_read(watertemp_t *watertemp, float *temperature)
{
  ESP_ERROR_CHECK(ds18b20_trigger_temperature_conversion(watertemp->ds18b20));
  ESP_ERROR_CHECK(ds18b20_get_temperature(watertemp->ds18b20, temperature));
  return 0;
}
