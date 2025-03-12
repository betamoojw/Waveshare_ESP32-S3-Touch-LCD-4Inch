#include <Arduino.h>
#include <ESP_Panel_Library.h>
#include <lvgl.h>
#include "lvgl_port_v8.h"

#include <ESP_IOExpander_Library.h>
// #include <demos/lv_demos.h>
// #include <examples/lv_examples.h>
#include <ui.h>
#include "HWCDC.h"

HWCDC USBSerial;

#define EXAMPLE_CHIP_NAME TCA95xx_8bit
#define EXAMPLE_I2C_NUM (1)
#define EXAMPLE_I2C_SDA_PIN (8)
#define EXAMPLE_I2C_SCL_PIN (9)

#define _EXAMPLE_CHIP_CLASS(name, ...) ESP_IOExpander_##name(__VA_ARGS__)
#define EXAMPLE_CHIP_CLASS(name, ...) _EXAMPLE_CHIP_CLASS(name, ##__VA_ARGS__)

ESP_IOExpander *expander = NULL;

void setup() {
  // expander = new EXAMPLE_CHIP_CLASS(EXAMPLE_CHIP_NAME,
  //                                   (i2c_port_t)EXAMPLE_I2C_NUM, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000,
  //                                   EXAMPLE_I2C_SCL_PIN, EXAMPLE_I2C_SDA_PIN);

  // expander->init();
  // // esp_err_t initStatus = expander->begin();
  // expander->begin();

  // if (initStatus == ESP_OK) {
    USBSerial.println("Expander initialized successfully.");
  // } else {
    expander = new EXAMPLE_CHIP_CLASS(EXAMPLE_CHIP_NAME,
                                      (i2c_port_t)1, ESP_IO_EXPANDER_I2C_TCA9554_ADDRESS_000,
                                      7, 15);
    expander->init();
    expander->begin();
  // }

  pinMode(16, OUTPUT); 
  digitalWrite(16, LOW);

  USBSerial.println("Original status:");
  expander->printStatus();
  expander->pinMode(5, OUTPUT);
  expander->digitalWrite(5, HIGH);
  expander->pinMode(0, OUTPUT);
  expander->digitalWrite(0, LOW);
  expander->pinMode(2, OUTPUT);
  expander->digitalWrite(2, LOW);
  expander->printStatus();
  delay(200);
  expander->digitalWrite(5, LOW);
  expander->digitalWrite(2, HIGH);
  expander->digitalWrite(0, HIGH);
  expander->printStatus();

  String title = "LVGL porting example";

  USBSerial.begin(115200);
  USBSerial.println(title + " start");

  USBSerial.println("Initialize panel device");
  ESP_Panel *panel = new ESP_Panel();
  panel->init();
#if LVGL_PORT_AVOID_TEAR
  // When avoid tearing function is enabled, configure the RGB bus according to the LVGL configuration
  ESP_PanelBus_RGB *rgb_bus = static_cast<ESP_PanelBus_RGB *>(panel->getLcd()->getBus());
  rgb_bus->configRgbFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
  rgb_bus->configRgbBounceBufferSize(LVGL_PORT_RGB_BOUNCE_BUFFER_SIZE);
#endif
  panel->begin();

  USBSerial.println("Initialize LVGL");
  lvgl_port_init(panel->getLcd(), panel->getTouch());

  USBSerial.println("Create UI");
  /* Lock the mutex due to the LVGL APIs are not thread-safe */
  lvgl_port_lock(-1);

  /* Create a simple label */
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, title.c_str());
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  ui_init();
  // lv_demo_widgets();
  // lv_demo_benchmark();
  // lv_demo_music();
  // lv_demo_stress();

  lvgl_port_unlock();

  USBSerial.println(title + " end");
}

void loop() {
  USBSerial.println("IDLE loop");
  delay(1000);
}
