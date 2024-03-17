#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../logic.h" // Заголовочный файл с функцией обработки строк

#define BUFF_SIZE 5000 // Определение размера буфера

int main() {
    char *pipe1 = "/tmp/pipe1";
    char *pipe2 = "/tmp/pipe2";

    char buffer[BUFF_SIZE];

    int pipe_fd1 = open(pipe1, O_RDONLY);
    ssize_t count = read(pipe_fd1, buffer, BUFF_SIZE);
    close(pipe_fd1);

    printf("Starting processing data...\n");
    edit_str(buffer);
    printf("Data processed successfully\n");
    printf("Writing to pipe2...\n");

    int pipe_fd2 = open(pipe2, O_WRONLY);
    write(pipe_fd2, buffer, count);
    close(pipe_fd2);

    unlink(pipe1);
    unlink(pipe2);

    return EXIT_SUCCESS;
}