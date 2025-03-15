#define EMBEDDED_CLI_IMPL
#include "cli_interface.h"
#include "cli_commands.h"
#include "HWCDC.h"

extern HWCDC USBSerial; // Declaration of the external USBSerial object

// Global CLI Variables (Definition)
EmbeddedCli *cli;
CLI_UINT cliBuffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE)];

void cli_init()
{
    EmbeddedCliConfig *config = embeddedCliDefaultConfig();
    config->cliBuffer = cliBuffer;
    config->cliBufferSize = CLI_BUFFER_SIZE;
    config->rxBufferSize = CLI_RX_BUFFER_SIZE;
    config->cmdBufferSize = CLI_CMD_BUFFER_SIZE;
    config->historyBufferSize = CLI_HISTORY_SIZE;
    config->maxBindingCount = CLI_BINDING_COUNT;

    cli = embeddedCliNew(config);

    if (cli == NULL)
    {
        USBSerial.println(F("Cli was not created. Check sizes!"));
        USBSerial.print(F("CLI_BUFFER_SIZE: "));
        USBSerial.println(CLI_BUFFER_SIZE);
        USBSerial.print(F("Required size: "));
        USBSerial.println(embeddedCliRequiredSize(config));
        while (1)
            ; // Halt if CLI fails to initialize
    }

    embeddedCliAddBinding(cli, {"clear",
                                "Clears the console",
                                true,
                                nullptr,
                                cli_clear});

    embeddedCliAddBinding(cli, {"version",
                                "Print version info",
                                true,
                                nullptr,
                                cli_version});

    embeddedCliAddBinding(cli, {"reboot",
                                "Reboot the device",
                                true,
                                nullptr,
                                cli_reboot});

    embeddedCliAddBinding(cli, {"hello",
                                "Print hello message",
                                true,
                                (void *)"Smart Panel",
                                cli_hello});

    embeddedCliAddBinding(cli, {"get-led",
                                "Get led status",
                                true,
                                nullptr,
                                cli_get_led});

    embeddedCliAddBinding(cli, {"set-led",
                                "Set led status",
                                true,
                                nullptr,
                                cli_set_led});

    embeddedCliAddBinding(cli, {"get-adc",
                                "Read adc value",
                                true,
                                nullptr,
                                cli_get_adc});

    embeddedCliAddBinding(cli, {"set-beeper",
                                "Set beeper tone",
                                true,
                                nullptr,
                                cli_set_beeper});
    embeddedCliAddBinding(cli, {"fs_test",
                                "File system test",
                                true,
                                nullptr,
                                cli_fs_test});

    cli->onCommand = cli_command;
    cli->writeChar = writeChar;
    USBSerial.println(F("Cli has started. Enter your commands."));
}

void cli_task()
{
    if (cli == NULL)
        return;

    while (USBSerial.available() > 0)
    {
        embeddedCliReceiveChar(cli, USBSerial.read());
    }
    embeddedCliProcess(cli);
}

void writeChar(EmbeddedCli *embeddedCli, char c)
{
    USBSerial.write((uint8_t *)&c, 1);
}
