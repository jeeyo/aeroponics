idf_component_register(
  SRCS  "main.c"
        "smartconfig_esptouch.c"
        "watertemp_ds18b20.c"
        "temphumid_dht11.c"
        "fogger_gpio.c"
        "mqtt_client.c"
  INCLUDE_DIRS ".")
