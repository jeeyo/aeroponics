#include "aeroponics.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

static const char *TAG = "AEROPONICS";

#define WATERTEMP_GPIO 0
#define TEMPHUMID_GPIO 1
#define FOGGER_GPIO    5

void app_main(void)
{
  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  // initialise_wifi();

  watertemp_t watertemp;
  watertemp_init(&watertemp, WATERTEMP_GPIO);

  // temphumid_t temphumid;
  // temphumid_init(&temphumid, TEMPHUMID_GPIO);

  fogger_t fogger;
  fogger_init(&fogger, FOGGER_GPIO);

  while (true)
  {
    vTaskDelay(pdMS_TO_TICKS(200));

    float water_temperature = 0.0f;
    watertemp_read(&watertemp, &water_temperature);
    ESP_LOGI(TAG, "Water temperature: %.2fC", water_temperature);

    // if (water_temperature > 28.6f) {
    //   fogger_write(&fogger, 0);
    //   ESP_LOGI(TAG, "Fogger off");
    // }

    // if (water_temperature < 27.0f) {
    //   fogger_write(&fogger, 1);
    //   ESP_LOGI(TAG, "Fogger on");
    // }

    // float environment_temperature = 0.0f;
    // float environment_humidity = 0.0f;
    // if (temphumid_read(&temphumid, &environment_temperature, &environment_humidity) == 0) {
    //   ESP_LOGI(TAG, "Environment temperature: %.1fC, humidity: %.1f%%", environment_temperature, environment_humidity);
    // }
  }
}
