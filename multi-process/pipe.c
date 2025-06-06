#include <stdio.h>       // printf, perror
#include <unistd.h>      // pipe, fork, read, write, close
#include <string.h>      // strlen
#include <sys/types.h>   // pid_t tipi

int main() {
    int pipefd[2];        // pipefd[0] = okuma ucu, pipefd[1] = yazma ucu
    pid_t pid;            // process ID
    char buffer[100];     // çocuk sürecin okuyacağı buffer

    // Pipe oluştur
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // fork ile çocuk süreç oluştur
    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // --- Çocuk süreç: sadece okur ---
        close(pipefd[1]); // yazma ucunu kapat
        read(pipefd[0], buffer, sizeof(buffer)); // pipe'dan oku
        printf("Çocuk süreç okudu: %s\n", buffer);
        close(pipefd[0]); // okuma ucunu kapat
    } else {
        // --- Ana süreç: sadece yazar ---
        close(pipefd[0]); // okuma ucunu kapat
        const char *msg = "Merhaba çocuk!";
        write(pipefd[1], msg, strlen(msg) + 1); // null byte dahil
        close(pipefd[1]); // yazma ucunu kapat
    }

    return 0;
}
