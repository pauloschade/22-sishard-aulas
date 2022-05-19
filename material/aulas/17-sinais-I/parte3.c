#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <time.h>

int main() {
    pid_t filho;

    filho = fork();
    if (filho == 0) {
        printf("%d\n", getpid());
        while(1) {

        }
    } else {
        int status,child_pid;
        sleep(10);
        if(!waitpid(filho, &status, WNOHANG)) {
            printf("gonna kill hahahah\n");
            kill(filho, SIGKILL);
        }
        child_pid = wait(&status);
        printf("filho acabou, %d\n", child_pid);
        printf("Error - %d\n", WIFEXITED(status));
        printf("Signal - %d\n", WIFSIGNALED(status));
        printf("%s\n", strsignal(WTERMSIG(status)));
    }

    return 0;
}