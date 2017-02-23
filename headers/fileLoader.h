#ifndef FILE_LOADER
#define FILE_LOADER

#include <SDL.h>
#include <cstring>
#include <iostream>

char* loadFile(const char* filename);
void writeFile(const char* filename, const char* data);
size_t fileSize(const char* filename);
char* loadFileSave(const char* filename);

#endif