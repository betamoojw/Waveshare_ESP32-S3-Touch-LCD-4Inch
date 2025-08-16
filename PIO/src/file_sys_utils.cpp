#include "FS.h"
#include <Arduino.h>
#include <LittleFS.h>
#include <Logger.h>

#define TAG "FS-UTILS"

#define FORMAT_LITTLEFS_IF_FAILED true

bool fs_mount()
{
    bool retVal = true;

    if (LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED))
    {
        LOG_I(TAG, "LittleFS Mount Successful");
    }
    else
    {
        LOG_E(TAG, "LittleFS Mount Failed");
        retVal = false;
    }

    return retVal;
}

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
    LOG_I(TAG, "Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root)
    {
        LOG_I(TAG, "- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        LOG_I(TAG, " - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            LOG_I(TAG, "  DIR : %s", file.name());
            if (levels)
            {
                listDir(fs, file.path(), levels - 1);
            }
        }
        else
        {
            LOG_I(TAG, "  FILE: %s", file.name());
            LOG_I(TAG, "\tSIZE: %d", file.size());
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char *path)
{
    LOG_I(TAG, "Creating Dir: %s\n", path);
    if (fs.mkdir(path))
    {
        LOG_I(TAG, "Dir created");
    }
    else
    {
        LOG_I(TAG, "mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char *path)
{
    LOG_I(TAG, "Removing Dir: %s\n", path);
    if (fs.rmdir(path))
    {
        LOG_I(TAG, "Dir removed");
    }
    else
    {
        LOG_I(TAG, "rmdir failed");
    }
}

void readFile(fs::FS &fs, const char *path)
{
    LOG_I(TAG, "Reading file: %s\r\n", path);

    File file = fs.open(path);
    if (!file || file.isDirectory())
    {
        LOG_I(TAG, "- failed to open file for reading");
        return;
    }

    LOG_I(TAG, "- read from file:");
    while (file.available())
    {
        SERIAL_DBG.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
    LOG_I(TAG, "Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        LOG_I(TAG, "- failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        LOG_I(TAG, "- file written");
    }
    else
    {
        LOG_I(TAG, "- write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message)
{
    LOG_I(TAG, "Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file)
    {
        LOG_I(TAG, "- failed to open file for appending");
        return;
    }
    if (file.print(message))
    {
        LOG_I(TAG, "- message appended");
    }
    else
    {
        LOG_I(TAG, "- append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char *path1, const char *path2)
{
    LOG_I(TAG, "Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2))
    {
        LOG_I(TAG, "- file renamed");
    }
    else
    {
        LOG_I(TAG, "- rename failed");
    }
}

void deleteFile(fs::FS &fs, const char *path)
{
    LOG_I(TAG, "Deleting file: %s\r\n", path);
    if (fs.remove(path))
    {
        LOG_I(TAG, "- file deleted");
    }
    else
    {
        LOG_I(TAG, "- delete failed");
    }
}

// SPIFFS-like write and delete file, better use #define CONFIG_LITTLEFS_SPIFFS_COMPAT 1

void writeFile2(fs::FS &fs, const char *path, const char *message)
{
    if (!fs.exists(path))
    {
        if (strchr(path, '/'))
        {
            LOG_I(TAG, "Create missing folders of: %s\r\n", path);
            char *pathStr = strdup(path);
            if (pathStr)
            {
                char *ptr = strchr(pathStr, '/');
                while (ptr)
                {
                    *ptr = 0;
                    fs.mkdir(pathStr);
                    *ptr = '/';
                    ptr = strchr(ptr + 1, '/');
                }
            }
            free(pathStr);
        }
    }

    LOG_I(TAG, "Writing file to: %s\r\n", path);
    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        LOG_I(TAG, "- failed to open file for writing");
        return;
    }
    if (file.print(message))
    {
        LOG_I(TAG, "- file written");
    }
    else
    {
        LOG_I(TAG, "- write failed");
    }
    file.close();
}

void deleteFile2(fs::FS &fs, const char *path)
{
    LOG_I(TAG, "Deleting file and empty folders on path: %s\r\n", path);

    if (fs.remove(path))
    {
        LOG_I(TAG, "- file deleted");
    }
    else
    {
        LOG_I(TAG, "- delete failed");
    }

    char *pathStr = strdup(path);
    if (pathStr)
    {
        char *ptr = strrchr(pathStr, '/');
        if (ptr)
        {
            LOG_I(TAG, "Removing all empty folders on path: %s\r\n", path);
        }
        while (ptr)
        {
            *ptr = 0;
            fs.rmdir(pathStr);
            ptr = strrchr(pathStr, '/');
        }
        free(pathStr);
    }
}

void testFileIO(fs::FS &fs, const char *path)
{
    LOG_I(TAG, "Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if (!file)
    {
        LOG_I(TAG, "- failed to open file for writing");
        return;
    }

    size_t i;
    LOG_I(TAG, "- writing");
    uint32_t start = millis();
    for (i = 0; i < 2048; i++)
    {
        if ((i & 0x001F) == 0x001F)
        {
            LOG_I(TAG, ".");
        }
        file.write(buf, 512);
    }
    LOG_I(TAG, "");
    uint32_t end = millis() - start;
    LOG_I(TAG, " - %u bytes written in %lu ms\r\n", 2048 * 512, end);
    file.close();

    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if (file && !file.isDirectory())
    {
        len = file.size();
        size_t flen = len;
        start = millis();
        LOG_I(TAG, "- reading");
        while (len)
        {
            size_t toRead = len;
            if (toRead > 512)
            {
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F)
            {
                LOG_I(TAG, ".");
            }
            len -= toRead;
        }
        LOG_I(TAG, "");
        end = millis() - start;
        LOG_I(TAG, "- %u bytes read in %lu ms\r\n", flen, end);
        file.close();
    }
    else
    {
        LOG_I(TAG, "- failed to open file for reading");
    }
}