// Leia o PDF ou MD antes de iniciar este exercício!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>


// Variável GLOBAL para armazenar o valor de PI aproximado
double pi = 0.0;

void config_sig( void (*f)(int), int activate) {
    struct sigaction s;
    s.sa_handler = (activate ? f: SIG_DFL);
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;
    sigaction(SIGINT, &s, NULL);
}

void log_pi() {
    int fd, n, i;
    char *path;
    n = 50;
    char output[n];
    char buf[1];

    snprintf(output, n, "%f", pi);
    path = "pi.txt";
    fd = open(path, O_WRONLY | O_CREAT, 0700);
    for(i=0; output[i] != '\0'; i++);
    write(fd, output, i);
}

void sig_handler_parent(int num) {
    printf("pi val: %f\n", pi);
    log_pi();
    config_sig(sig_handler_parent, 0);
    kill(getpid(), SIGINT);
}

// Função que gera um numero aleatorio uniformemente entre 0.0 e 1.0
// Você não deve alterar esta função
double random_zero_one() {
    return (double)random()/(double)RAND_MAX;
}

// Função que calcula o valor de pi por simulação (Monte Carlo)
// Você não deve alterar esta função
double aproxima_pi() {
    long dentro = 0;
    long total_pontos = 0;

    double x,y,d;
    while (1) {
        x = random_zero_one();
        y = random_zero_one();
        d = x*x + y*y;
        if (d<=1) {
            dentro++;
        }
        total_pontos++;
        pi = 4.0 * ((double)dentro/(double)total_pontos);
        if (random_zero_one() < 0.008) {
            sleep(1);
        }
    }
}

// Crie AQUI a função que exporta o valor de pi para um arquivo chamado pi.txt
// Esta função deve ser chamada pelo handler quando este for acionado

// Crie AQUI a função que será o handler do sinal

int main() {

    // Exiba o PID deste processo
    printf("proc id %d\n", getpid());
    // Registre AQUI seu handler para o sinal SIGINT!
    config_sig(sig_handler_parent, 1);

    srand(time(NULL));
    aproxima_pi();

    return 0;
}