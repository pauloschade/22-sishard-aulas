#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int status = 0;

void operacao_lenta() {
    sleep(10);
}


void sigint_handler(int num) {
    status += 1;
    printf("Chamou Ctrl+C; status=%d\n", status);
    operacao_lenta();
    printf("SIGINT: Vou usar status agora! status=%d\n", status);
}

void sigterm_handler(int num) {
    status += 1;
    printf("Recebi SIGTERM; status=%d\n", status);
    operacao_lenta();
    printf("SIGTERM: Vou usar status agora! status=%d\n", status);
}

int main() {
    struct sigaction s1;
    struct sigaction s2;
    printf("Meu pid: %d\n", getpid());

    s1.sa_handler = sigint_handler; // aqui vai a função a ser executada
    sigemptyset(&s1.sa_mask);
    sigaddset(&s1.sa_mask, SIGTERM);
    s1.sa_flags = 0;

    s2.sa_handler = sigterm_handler; // aqui vai a função a ser executada
    sigemptyset(&s2.sa_mask);
    sigaddset(&s2.sa_mask, SIGINT);
    s2.sa_flags = 0;

    sigaction(SIGINT, &s1, NULL);
    sigaction(SIGTERM, &s2, NULL);

    printf("Meu pid: %d\n", getpid());

    while(1) {
        sleep(1);
    }
    return 0;
}
