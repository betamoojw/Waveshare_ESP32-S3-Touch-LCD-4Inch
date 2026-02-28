#ifndef CLI_COMMANDS_H
#define CLI_COMMANDS_H

#include "embedded_cli.h"
#include <Arduino.h>

void cli_command(EmbeddedCli *embeddedCli, CliCommand *command);
void cli_clear(EmbeddedCli *cli, char *args, void *context);
void cli_version(EmbeddedCli *cli, char *args, void *context);
void cli_reboot(EmbeddedCli *cli, char *args, void *context);
void cli_hello(EmbeddedCli *cli, char *args, void *context);

void cli_get_led(EmbeddedCli *cli, char *args, void *context);
void cli_set_led(EmbeddedCli *cli, char *args, void *context);
void cli_get_adc(EmbeddedCli *cli, char *args, void *context);

void cli_set_beeper(EmbeddedCli *cli, char *args, void *context);

void cli_fs_test(EmbeddedCli *cli, char *args, void *context);
#endif