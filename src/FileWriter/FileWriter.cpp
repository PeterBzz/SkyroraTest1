
#include "FileWriter.h"

void WriteTelemetry(string fileName, string text)
{
    int file = open(fileName.c_str(), O_WRONLY | O_CREAT | O_APPEND);
    write(file, text.c_str(), text.length());
    close(file);
}
