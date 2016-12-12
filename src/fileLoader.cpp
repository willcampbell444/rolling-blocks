#include <fileLoader.h>

char* loadFile(const char* filename) {
    SDL_RWops* file = SDL_RWFromFile(filename, "rb");
    if (file != NULL) {
        size_t filesize = SDL_RWsize(file);

        char *buffer = new char[filesize + 1];
        
        int nb_read_total = 0, nb_read = 1;
        char* buf = buffer;
        while (nb_read_total < filesize && nb_read != 0) {
            nb_read = SDL_RWread(file, buf, 1, (filesize - nb_read_total));
            nb_read_total += nb_read;
            buf += nb_read;
        }
        SDL_RWclose(file);
        if (nb_read_total != filesize) {
            free(buffer);
            return NULL;
        }
        
        buffer[nb_read_total] = '\0';
        return buffer;
    }
    return NULL;
}

void writeFile(const char* filename, const char* data) {
    SDL_RWops* file = SDL_RWFromFile(filename, "w");

    SDL_RWwrite(file, data, 1, strlen(data));
}