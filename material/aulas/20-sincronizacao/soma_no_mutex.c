#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct soma_parcial_args {
    double *vetor;
    int start, end;
    double soma;
};

void *soma_parcial(void *_arg) {
    struct soma_parcial_args *spa = _arg;
    double sum = 0;

    for (int i = spa->start; i < spa->end; i++) {
        sum += spa->vetor[i];
    }

    spa -> soma = sum;
    return NULL;
}

int main(int argc, char *argv[]) {
    double *vetor = NULL;
    int n;
    scanf("%d", &n);

    vetor = malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &vetor[i]);
    }


    /* TODO: criar thread_t e soma_parcial_args aqui */
    pthread_t *tid = malloc(sizeof(pthread_t) * 4);
    struct soma_parcial_args *args = malloc(sizeof(struct soma_parcial_args) * 4) ;

    for (int i = 0; i < 4; i++) {
        /* TODO: preencher args e lançar thread */
        args[i].vetor = vetor;
        args[i].start = i*n/4;
        args[i].end = (i+1)*n/4;
        args[i].soma = 0;
        pthread_create(&tid[i], NULL, soma_parcial, &args[i]);
    }

    /* TODO: esperar pela conclusão*/

    for (int i = 0; i < 4; i++) {
        pthread_join(tid[i], NULL);
    }

    double total_sum = 0;
    for (int i = 0; i < 4; i++) {
        total_sum += args[i].soma;
    }

    printf("Paralela: %lf\n", total_sum);

    struct soma_parcial_args aa;
    aa.vetor = vetor;
    aa.start = 0;
    aa.end = n;
    soma_parcial(&aa);
    printf("Sequencial: %lf\n", aa.soma);

    return 0;
}
