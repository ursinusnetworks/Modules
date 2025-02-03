#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* f = fopen("out.txt", "w");
    fprintf(f, "eenie ");
    fclose(f);
    f = fopen("out.txt", "w");
    fprintf(f, "meenie ");
    fclose(f);
    f = fopen("out.txt", "a");
    fprintf(f, "miney moe");
    fclose(f);
}