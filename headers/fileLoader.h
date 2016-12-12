#ifndef FILE_LOADER
#define FILE_LOADER

#include <SDL.h>
#include <cstring>

char* loadFile(const char* filename);
void writeFile(const char* filename, const char* data);

#endif