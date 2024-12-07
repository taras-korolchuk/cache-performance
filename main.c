#include "config.h"

int main() {
    int* array = malloc(sizeof(int) * ARRAY_SIZE);
    if (!array) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    const clock_t start_time = clock();

#if ATOMIC_MEMORY
    printf("Atomic memory mode\n");
    atomic_int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        atomic_fetch_add(&sum, 1);
    }
    printf("Result: %d\n", sum);

#elif CACHE_DELAYS
    printf("Cache delays mode\n");
    volatile int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    printf("Result: %d\n", sum);

#elif CACHE_MISSES
    printf("Cache misses mode\n");
    int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE; i += 16) {
        sum += array[i];
    }
    printf("Result: %d\n", sum);

#elif RANDOM_MEMORY
    printf("Random memory mode\n");
    int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        const size_t index = rand() % ARRAY_SIZE;
        sum += array[index];
    }
    printf("Result: %d\n", sum);

#elif SEQUENTIAL_MEMORY
    printf("Sequential memory mode\n");
    int sum = 0;
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
    }
    printf("Result: %d\n", sum);

#endif

    const clock_t end_time = clock();
    const double latency = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Latency: %f seconds\n", latency);

    free(array);
    return 0;
}
