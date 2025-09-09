#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Bad args:");
    }

    FILE* ifile = fopen(argv[2], "rb");
    if (ifile == NULL) {
        perror("Inputfile error:");
        return 1;
    }
    
    FILE* ofile = fopen("converted.txt", "w");
    if (ofile == NULL) {
        perror("Outfile error:");
        fclose(ofile);
        return 1;
    }

    char buffer[1024];
    size_t bytes_read;

    if (strcmp(argv[1], "-b") == 0) {
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), ifile)) > 0) {
            for (size_t i = 0; i < bytes_read; i++) {
                for (int j = 7; j >= 0; j--) {
                    fprintf(ofile, "%d", (buffer[i] >> j) & 1);
                }
            }
        }
        fclose(ifile);
        fclose(ofile);
    }

    else if (strcmp(argv[1], "-h") == 0) {
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), ifile)) > 0) {
            for (size_t i = 0; i < bytes_read; i++) {
                fprintf(ofile, "%02X", buffer[i]);
            }
        }
        fclose(ifile);
        fclose(ofile);
    }

    else {
        printf("Invalid arg: %s", argv[1]);
        fclose(ifile);
        fclose(ofile);
        return 1;
    }

    return 0;
}