#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../logic.h" // Заголовочный файл с функцией обработки строк

#define BUFF_SIZE 128 // Определение размера буфера

int main() {
    char *pipe1 = "/tmp/pipe1";
    char *pipe2 = "/tmp/pipe2";

    char buffer[BUFF_SIZE];

    int pipe_fd1 = open(pipe1, O_RDONLY);
    int pipe_fd2 = open(pipe2, O_WRONLY);

    ssize_t count;
    while ((count = read(pipe_fd1, buffer, BUFF_SIZE)) > 0) {
        printf("Starting processing data...\n");
        edit_str(buffer);
        printf("Data processed successfully\n");

        write(pipe_fd2, buffer, count);
    }

    close(pipe_fd1);
    close(pipe_fd2);

    return EXIT_SUCCESS;
}