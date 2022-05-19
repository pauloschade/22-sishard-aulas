/* POSIX headers */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* Standard C */
#include <stdio.h>

int main (int argc, char *argv[]) {
    char arq1[100]; // nomes do arquivo, recebido via scanf
    char arq2[100]; // nomes do arquivo, recebido via scanf
    char buf[1]; // local usado para guardar os dados lidos de arq1
    int n_read = 1;
    
    scanf("%s", arq1);
    int fd1 = open(arq1, O_RDONLY);

    scanf("%s", arq2);
    int fd2 = open(arq2, O_WRONLY | O_CREAT, 0640);

    for (int i = 0; n_read > 0; i++) {
        n_read = read(fd1, buf, 1);
        if(n_read != 0) {
            write(fd2, buf, 1);
        }
    }
    close(fd1);
    
    return 0;
}