#define SMARTPANEL_DEFINE_GLOBAL_VARS // only in one source file, main.cpp!
#include "main.h"
#include <Arduino.h>
#include "HWCDC.h"
#include <LittleFS.h>
#include "file_sys_utils.h"
#include <ESP_Panel_Library.h>
#include <lvgl.h>
#include "lvgl_port_v8.h"

#include <ESP_IOExpander_Library.h>
#include "io_expander_warapper.h"
// #include <demos/lv_demos.h>
// #include <examples/lv_examples.h>
#include <ui.h>

#include "web_server.h"

HWCDC USBSerial; // Definition of the USBSerial object

#if defined(SMARTPANEL_ENABLE_RS485)
#include <HardwareSerial.h>
HardwareSerial SerialPort(2); // use UART2

void task_rs485_interface_loop(void *pvParameters)
{
  while (1)
  {
    if (Serial2.available())
    {
      char buffer[256];      // Buffer to store input data
      size_t bufferSize = 0; // Current size of data in buffer

      while (Serial2.available() > 0)
      {
        char input = Serial2.read();

        // Check if the buffer is full, or a newline character is received
        if (bufferSize >= sizeof(buffer) || input == '\r')
        {
          // Send the entire buffer via Serial2
          Serial2.println(buffer);
          USBSerial.println(buffer);
          delay(10);
          // Reset buffer and size for the next input
          bufferSize = 0;
          memset(buffer, 0, sizeof(buffer));
        }
        else
          buffer[bufferSize++] = input; // Store input in buffer
      }
    }
    delay(1);
  }
}
#endif

#if defined(SMARTPANEL_ENABLE_CAN)
#include "twai_port.h"
#endif

#if defined(SMARTPANEL_ENABLE_CLI)
#include "cli_interface.h"
#endif

#include "beeper.h"

static bool driver_installed = false; // Flag to check if the driver is installed
ESP_IOExpander *expander = NULL;

void setup()
{
  USBSerial.begin(115200);
  USBSerial.println("USBSerial initialized.");

  char msg[128];
  snprintf(msg, sizeof(msg), "---Smart Panel: %s %d INIT---", SMARTPANEL_VERSION, VERSION);
  USBSerial.println(msg);

  fs_mount();

  pinMode(TP_INT_PIN, OUTPUT);
  digitalWrite(TP_INT_PIN, LOW);

  // Initialize the IO expander
  io_expander_init(expander);

  String title = "Smart Panel";

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

#if defined(SMARTPANEL_ENABLE_RS485)
  Serial2.begin(115200, SERIAL_8N1, RS485_RXD_PIN, RS485_TXD_PIN);
#endif

#if defined(SMARTPANEL_ENABLE_CAN)
  driver_installed = twai_init();
#endif

#if defined(SMARTPANEL_ENABLE_CLI)
  cli_init();
#endif

}

void loop()
{
#if defined(SMARTPANEL_ENABLE_CLI)
  cli_task();
#endif

#if defined(SMARTPANEL_ENABLE_RS485)
  task_rs485_interface_loop(NULL);
#endif

#if defined(SMARTPANEL_ENABLE_CAN)
  twai_task();
#endif

}
