#include "cli_commands.h"
#include "FS.h"
#include <LittleFS.h>
#include "file_sys_utils.h"
#include <ESP_IOExpander_Library.h>
#include "main.h"

#include <Logger.h>

#define TAG "CLI-COMMANDS"
#define CLI_INTERFACE_VERSION "0.0.1"

void cli_command(EmbeddedCli *embeddedCli, CliCommand *command)
{
    LOG_I(TAG, "Received command: %S", command->name);
    embeddedCliTokenizeArgs(command->args);
    for (int i = 1; i <= embeddedCliGetTokenCount(command->args); ++i) {
        const char *arg = embeddedCliGetToken(command->args, i);
        LOG_I(TAG, "arg %d: %s", i, arg);
    }
}
void cli_clear(EmbeddedCli *cli, char *args, void *context)
{
    LOG_I(TAG, F("\33[2J"));
}
void cli_version(EmbeddedCli *cli, char *args, void *context)
{
    LOG_I(TAG, "CLI-Version: %S", CLI_INTERFACE_VERSION);
}
void cli_reboot(EmbeddedCli *cli, char *args, void *context)
{
    LOG_I(TAG, "Rebooting...");
    delay(1000);
    ESP.restart();
}
void cli_hello(EmbeddedCli *cli, char *args, void *context)
{
    LOG_I(TAG, "Hello ");
    if (args == NULL || embeddedCliGetTokenCount(args) == 0)
    {
        LOG_I(TAG, (const char *)context);
    }
    else
    {
        const char *name = embeddedCliGetToken(args, 1);
        if (name != NULL)
        {
            LOG_I(TAG, name);
        }
        else
        {
            LOG_I(TAG, F("stranger"));
        }
    }
}

void cli_get_led(EmbeddedCli *cli, char *args, void *context)
{
    const char *arg1 = embeddedCliGetToken(args, 1);
    if (arg1 == NULL) {
        LOG_I(TAG, "Usage: get-led [arg1]");
        return;
    }

    LOG_I(TAG, "Get LED with args: %s, status: %d", arg1, random(0, 2));
}
void cli_set_led(EmbeddedCli *cli, char *args, void *context)
{
    if ((args == NULL) || (embeddedCliGetTokenCount(args) < 2))
    {
        LOG_I(TAG, "Usage: set-led [arg1] [arg2]");
        return;
    }

    const char *arg1 = embeddedCliGetToken(args, 1);
    const char *arg2 = embeddedCliGetToken(args, 2);

    LOG_I(TAG, "Set LED with args: %s and %s", arg1, arg2);
}
void cli_get_adc(EmbeddedCli *cli, char *args, void *context)
{
    const char *arg1 = embeddedCliGetToken(args, 1);
    if (arg1 == NULL) {
        LOG_I(TAG, "Usage: get-adc [arg1]");
        return;
    }

    LOG_I(TAG, "Get ADC with args: %s, result: %d", arg1, random(1024));
}

void cli_set_beeper(EmbeddedCli *cli, char *args, void *context)
{
    if ((args == NULL) || (embeddedCliGetTokenCount(args) < 2))
    {
        LOG_I(TAG, "Usage: set-beeper [arg1] [arg2]");
        return;
    }

    const char *arg1 = embeddedCliGetToken(args, 1);
    const char *arg2 = embeddedCliGetToken(args, 2);

    LOG_I(TAG, "Set beeper with args: %s and %s", arg1, arg2);
}

void cli_fs_test(EmbeddedCli *cli, char *args, void *context)
{
    testFileIO(LittleFS, "/test.txt");
    deleteFile(LittleFS, "/test.txt");
}