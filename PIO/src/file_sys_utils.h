#ifndef FILE_SYS_UTILS_H
#define FILE_SYS_UTILS_H

#include <FS.h> // Include the base class for file systems

bool fs_mount();

/**
 * @brief Lists the contents of a directory on the file system.
 *
 * @param fs      A reference to the file system object (e.g., SPIFFS, LittleFS, SD).
 * @param dirname The path to the directory to list.
 * @param levels  The number of subdirectory levels to recursively list.
 */
void listDir(fs::FS &fs, const char *dirname, uint8_t levels);

/**
 * @brief Creates a new directory on the file system.
 *
 * @param fs   A reference to the file system object.
 * @param path The path where the new directory should be created.
 */
void createDir(fs::FS &fs, const char *path);

/**
 * @brief Removes a directory from the file system.  The directory must be empty.
 *
 * @param fs   A reference to the file system object.
 * @param path The path to the directory to remove.
 */
void removeDir(fs::FS &fs, const char *path);

/**
 * @brief Reads the contents of a file and prints them to the Serial monitor.
 *
 * @param fs   A reference to the file system object.
 * @param path The path to the file to read.
 */
void readFile(fs::FS &fs, const char *path);

/**
 * @brief Writes a string to a file on the file system, overwriting any existing content.
 *
 * @param fs      A reference to the file system object.
 * @param path    The path to the file to write.
 * @param message The string to write to the file.
 */
void writeFile(fs::FS &fs, const char *path, const char *message);

/**
 * @brief Appends a string to the end of a file on the file system.
 *
 * @param fs      A reference to the file system object.
 * @param path    The path to the file to append to.
 * @param message The string to append to the file.
 */
void appendFile(fs::FS &fs, const char *path, const char *message);

/**
 * @brief Renames a file on the file system.
 *
 * @param fs    A reference to the file system object.
 * @param path1 The current path of the file.
 * @param path2 The new path for the file.
 */
void renameFile(fs::FS &fs, const char *path1, const char *path2);

/**
 * @brief Deletes a file from the file system.
 *
 * @param fs   A reference to the file system object.
 * @param path The path to the file to delete.
 */
void deleteFile(fs::FS &fs, const char *path);

/**
 * @brief Writes a string to a file, creating missing directories in the path if necessary.
 *
 * @param fs      A reference to the file system object.
 * @param path    The path to the file to write.
 * @param message The string to write to the file.
 */
void writeFile2(fs::FS &fs, const char *path, const char *message);

/**
 * @brief Deletes a file and attempts to remove any empty directories in the path.
 *
 * @param fs   A reference to the file system object.
 * @param path The path to the file to delete.
 */
void deleteFile2(fs::FS &fs, const char *path);

/**
 * @brief Tests file I/O performance by writing and reading a large file.
 *
 * @param fs   A reference to the file system object.
 * @param path The path to the file to use for testing.
 */
void testFileIO(fs::FS &fs, const char *path);

#endif