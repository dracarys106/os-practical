#include <stdio.h>
#include <pthread.h>

#define THREADS 4
#define N 100

int numbers[N];
long long partial[THREADS];

struct Range {
    int start;
    int end;
    int thread_id;
};

void *sum_range(void *arg) {
    struct Range *r = (struct Range *)arg;
    partial[r->thread_id] = 0;

    for (int i = r->start; i < r->end; i++)
        partial[r->thread_id] += numbers[i];

    printf("Thread %d: partial sum = %lld\n",
           r->thread_id + 1, partial[r->thread_id]);
    return NULL;
}

int main(void) {
    pthread_t threads[THREADS];
    struct Range ranges[THREADS];
    long long total = 0;

    for (int i = 0; i < N; i++) numbers[i] = i + 1;

    for (int i = 0; i < THREADS; i++) {
        ranges[i].start = i * (N / THREADS);
        ranges[i].end = (i + 1) * (N / THREADS);
        ranges[i].thread_id = i;
        if (pthread_create(&threads[i], NULL, sum_range, &ranges[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < THREADS; i++) total += partial[i];
    printf("Sum of first %d numbers = %lld\n", N, total);
    return 0;
}
