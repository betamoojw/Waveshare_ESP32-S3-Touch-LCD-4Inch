#define EMBEDDED_CLI_IMPL
#include "cli_interface.h"
#include "cli_commands.h"
#include <Logger.h>

// Global CLI Variables (Definition)
EmbeddedCli *cli;
CLI_UINT cliBuffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE)];

#define TAG "CLI-INTERFACE"

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
        LOG_E(TAG, "Cli was not created. Check sizes!");
        LOG_E(TAG, "CLI_BUFFER_SIZE: %d", CLI_BUFFER_SIZE);
        LOG_E(TAG, "Required size: %d", embeddedCliRequiredSize(config));
        while (1)
            ; // Halt if CLI fails to initialize
    }

    embeddedCliAddBinding(cli, {"clear", "Clears the console", true, nullptr, cli_clear});

    embeddedCliAddBinding(cli, {"version", "Print version info", true, nullptr, cli_version});

    embeddedCliAddBinding(cli, {"reboot", "Reboot the device", true, nullptr, cli_reboot});

    embeddedCliAddBinding(cli, {"hello", "Print hello message", true, (void *) "Smart Panel", cli_hello});

    embeddedCliAddBinding(cli, {"get-led", "Get led status", true, nullptr, cli_get_led});

    embeddedCliAddBinding(cli, {"set-led", "Set led status", true, nullptr, cli_set_led});

    embeddedCliAddBinding(cli, {"get-adc", "Read adc value", true, nullptr, cli_get_adc});

    embeddedCliAddBinding(cli, {"set-beeper", "Set beeper tone", true, nullptr, cli_set_beeper});
    embeddedCliAddBinding(cli, {"fs_test", "File system test", true, nullptr, cli_fs_test});

    cli->onCommand = cli_command;
    cli->writeChar = writeChar;
    LOG_I(TAG, "Cli has started. Enter your commands.");
}

void cli_task()
{
    if (cli == NULL)
        return;

    while (SERIAL_DBG.available() > 0)
    {
        embeddedCliReceiveChar(cli, SERIAL_DBG.read());
    }
    embeddedCliProcess(cli);
}

void writeChar(EmbeddedCli *embeddedCli, char c)
{
    SERIAL_DBG.write((uint8_t *) &c, 1);
}
