#ifndef _AEROPONICS_H
#define _AEROPONICS_H

#include "onewire_bus.h"
#include "ds18b20.h"
#include "mqtt_client.h"

typedef struct {
  onewire_device_t onewire_device;
  ds18b20_device_handle_t ds18b20;
} watertemp_t;

int watertemp_init(watertemp_t *watertemp, int gpio);             // initialize a one-wire ds18b20
int watertemp_read(watertemp_t *watertemp, float *temperature);   // return temperature in Celsius

typedef struct {
  int gpio;
} temphumid_t;

int temphumid_init(temphumid_t *temphumid, int gpio);                             // initialize a DHT11
int temphumid_read(temphumid_t *temphumid, float *temperature, float *humidity);  // return temperature in Celsius and relative humidity in %

typedef struct {
  int gpio;
} fogger_t;

int fogger_init(fogger_t *fogger, int gpio);
void fogger_write(fogger_t *fogger, int onoff);

void initialise_wifi(void);

#define MQTT_BROKER_URL "mqtt://192.168.1.43"

typedef struct {
  esp_mqtt_client_handle_t handle;
} mqtt_client_t;

void mqtt_client_init(mqtt_client_t *client);
int mqtt_client_publish(mqtt_client_t *client, const char *topic, const char *data, int data_len, int qos);
int mqtt_is_connected();

#endif /* _AEROPONICS_H */
