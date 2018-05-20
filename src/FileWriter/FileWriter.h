
#ifndef FileWriter_H
#define FileWriter_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>

using namespace std;

void WriteTelemetry(string fileName, string text);

#endif
