// Leia o PDF ou MD antes de iniciar este exercício!

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc != 4) {
        printf("q2: must provide 3 args\n");
        return -1;
    }
    char *path;
    path = "./siscoin";

    int ret;
    int st;

    do {
        if(fork() == 0) {
            char *args[] = {path, argv[1], argv[2], argv[3], NULL};
            execvp(path, args);
        }
        wait(&st);
        if (WIFEXITED(st)) {
            ret = (char) WEXITSTATUS(st);
        }
    } while (ret > 0); // Repita enquanto houver falha. 
                       // Para se tem problema com o valor ou a qtde de parâmetros
                       // Esta validação está sendo feita em siscoin
    printf("transfered\n");

    return 0;
}