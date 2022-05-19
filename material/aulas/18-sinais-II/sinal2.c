#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int c = 0;
void sig_handler(int num) {
    printf("Chamou Ctrl+C\n");
    if(c == 1) {
        struct sigaction s;
        s.sa_handler = SIG_DFL; // aqui vai a função a ser executada
        sigemptyset(&s.sa_mask);
        s.sa_flags = 0;
        sigaction(SIGINT, &s, NULL);
    }
    c++;

}

int main() {
    struct sigaction s;
    printf("Meu pid: %d\n", getpid());

    s.sa_handler = sig_handler; // aqui vai a função a ser executada
    sigemptyset(&s.sa_mask);
    s.sa_flags = 0;

    sigaction(SIGINT, &s, NULL);
    while(1) {
        sleep(1);
    }
    return 0;
}
