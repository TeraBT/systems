#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    int elements = atoi(argv[1]);
    long long *array = malloc(sizeof(long long) * elements);

    array[1] = 1;

    for (int i = 2; i < elements; i++) {
        array[i] = array[i-1] + array[i-2];
    }

    for (int i = 0; i < elements; i++) {
        printf("%lld ", array[i]);
    }

    printf("\n");

    return EXIT_SUCCESS;
}