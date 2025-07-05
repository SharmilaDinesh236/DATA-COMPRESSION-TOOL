#include <stdio.h>
#include <stdlib.h>

// ?? Compress the content of input file and write to compressed file
void compressFile(const char *inputFile, const char *compressedFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(compressedFile, "w");

    if (in == NULL || out == NULL) {
        printf("? Error: Cannot open file(s).\n");
        return;
    }

    char current, previous;
    int count = 1;

    previous = fgetc(in);
    if (previous == EOF) {
        printf("? Input file is empty.\n");
        fclose(in);
        fclose(out);
        return;
    }

    printf("\n?? Compressed Output:\n");

    while ((current = fgetc(in)) != EOF) {
        if (current == previous) {
            count++;
        } else {
            fprintf(out, "%c%d", previous, count);
            printf("%c%d", previous, count);  // ?? Print to screen
            previous = current;
            count = 1;
        }
    }

    fprintf(out, "%c%d", previous, count);
    printf("%c%d\n", previous, count);  // ?? Print last part

    fclose(in);
    fclose(out);

    printf("? Compression completed! Output saved in '%s'.\n", compressedFile);
}

// ?? Decompress the content of compressed file and write to output file
void decompressFile(const char *compressedFile, const char *outputFile) {
    FILE *in = fopen(compressedFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("? Error: Cannot open file(s).\n");
        return;
    }

    char ch;
    int count;
    int i;

    printf("\n?? Decompressed Output:\n");

    while (fscanf(in, "%c%d", &ch, &count) == 2) {
        for (i = 0; i < count; i++) {
            fputc(ch, out);
            printf("%c", ch);  // ?? Print to screen
        }
    }

    printf("\n");

    fclose(in);
    fclose(out);

    printf("? Decompression completed! Output saved in '%s'.\n", outputFile);
}

// ?? Main function
int main() {
    char inputFile[] = "myfile.txt";
    char compressedFile[] = "compressed.txt";
    char decompressedFile[] = "decompressed.txt";

    compressFile(inputFile, compressedFile);
    decompressFile(compressedFile, decompressedFile);

    return 0;
}
