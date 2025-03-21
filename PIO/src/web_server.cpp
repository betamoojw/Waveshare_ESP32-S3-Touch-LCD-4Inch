#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "main.h"
#include "HWCDC.h"

extern HWCDC USBSerial; // Declaration of the external USBSerial object

AsyncWebServer server(80);

const char *ssid = "MX-09-1502";
const char *password = "Moojw2024";

const char *PARAM_MESSAGE = "message";

static void notFound(AsyncWebServerRequest *request)
{
    request->send(404, "text/plain", "Not found");
}

void ws_init()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        USBSerial.printf("WiFi Failed!\n");
        return;
    }

    USBSerial.print("IP Address: ");
    USBSerial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hello, world"); });

    // Send a GET request to <IP>/get?message=<message>
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message); });

    // Send a POST request to <IP>/post with a form field message set to <message>
    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message); });

    server.onNotFound(notFound);

    server.begin();
}

void ws_task()
{
}