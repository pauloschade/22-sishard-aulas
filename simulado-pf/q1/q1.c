// Leia o PDF ou MD antes de iniciar este exercício!
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Faça os includes necessários aqui
// #include ...

typedef struct {
    sem_t *s1;
    sem_t *s2;
} semaphors;

void *thread1(void *_arg) {
    semaphors *sems = _arg;

    for(int i=0; i<3; i++) {
        sem_post(sems -> s1);
    }
    printf("A\n");

    for(int i=0; i<3; i++) {
        sem_wait(sems -> s2);
    }

    printf("E\n");

    return NULL;
}

void *thread2(void *_arg) {
    semaphors *sems = _arg;

    sem_wait(sems -> s1);
    printf("B\n");
    sem_post(sems -> s2);

    return NULL;
}

void *thread3(void *_arg) {
    semaphors *sems = _arg;

    sem_wait(sems -> s1);
    printf("C\n");
    sem_post(sems -> s2);

    return NULL;
}

void *thread4(void *_arg) {
    semaphors *sems = _arg;

    sem_wait(sems -> s1);
    printf("D\n");
    sem_post(sems -> s2);

    return NULL;
}

int main(int argc, char *argv[]) {
    sem_t s1, s2;
    int n = 4;

    semaphors *sems = malloc(sizeof(semaphors));

    sem_init(&s1, 0, 0);
    sem_init(&s2, 0, 0);

    sems -> s1 = &s1;
    sems -> s2 = &s2;

    pthread_t *tid = malloc(sizeof(pthread_t) * n);

    pthread_create(&tid[0], NULL, thread1, sems);
    pthread_create(&tid[1], NULL, thread2, sems);
    pthread_create(&tid[2], NULL, thread3, sems);
    pthread_create(&tid[3], NULL, thread4, sems);

    for (int i = 0; i < n; i++) {
        pthread_join(tid[i], NULL);
    }
    
    free(sems);
    free(tid);


    // Espere por TODAS as threads
    
    
    return 0;
}