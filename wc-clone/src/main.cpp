#include <iostream>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

using namespace std;

int main(int argc, char **argv) {

    if (argc < 2) {
        cout << "Please specify a file or files!" << endl;
        return 1;
    }

    system("pwd");
    
    for (size_t i = 1; i < argc; i++) {

        // select current argument file name and open file
        char* file_name = argv[i];
        FILE* fptr = fopen(file_name, "r");

        if (fptr) {

            // check file size
            fseek(fptr, 0, SEEK_END);
            const size_t NUM_BYTES = ftell(fptr);
            rewind(fptr);

            // create buffer to handle size and read file to buffer
            char* buf = (char*) calloc(NUM_BYTES, sizeof(char));
            fread(buf, 1, NUM_BYTES, fptr);

            // setup counters
            size_t n_count = 0;
            size_t word_count = 0;
            size_t char_count = 0;
            bool last_space = false;

            // single-pass check
            for (size_t j = 0; j < NUM_BYTES; j++) {

                if (isspace(buf[j])) {
                    if (last_space) {
                        word_count++;
                    }
                    if (buf[j] == '\n') {
                        n_count++;
                    }
                    last_space = true;
                } else {
                    char_count++;
                    last_space = false;
                }

            }

            size_t line_count = n_count + 1;

            printf("\t%d\t%d\t%d\t%s\n", line_count, word_count, char_count, file_name);
            fclose(fptr);
            free(buf);

        } else {
            printf("File \"%s\" does not exist!\n", file_name);
        }
    }
    
    return 0;
}
