#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int pipefd[2]; // pipefd[0] = read, pipefd[1] = write
    pid_t pid;
    char buffer[100];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Çocuk süreç: okumayla ilgilenir
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Çocuk süreç okudu: %s\n", buffer);
    } else {
        // Ebeveyn süreç: yazma işlemi yapar
        close(pipefd[0]);
        char *msg = "Merhaba çocuk!";
        write(pipefd[1], msg, strlen(msg) + 1);
    }

    return 0;
}
