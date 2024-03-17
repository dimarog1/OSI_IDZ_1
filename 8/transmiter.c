#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "../logic.h" // Заголовочный файл с функцией обработки строк

#define BUFF_SIZE 5000 // Определение размера буфера

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *pipe1 = "/tmp/pipe1";
    char *pipe2 = "/tmp/pipe2";

    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd == -1) {
        perror("Error reading from input file");
        exit(EXIT_FAILURE);
    }
    printf("Input file read successfully\n");

    if (access(pipe1, F_OK) == -1) {
        if (mkfifo(pipe1, 0666) == -1) {
            perror("Error creating pipe1");
            exit(EXIT_FAILURE);
        }
    }

    if (access(pipe2, F_OK) == -1) {
        if (mkfifo(pipe2, 0666) == -1) {
            perror("Error creating pipe2");
            exit(EXIT_FAILURE);
        }
    }

    char buffer[BUFF_SIZE];

    printf("Waiting for receiver to read from pipe1...\n");

    ssize_t count = read(file_fd, buffer, BUFF_SIZE);
    close(file_fd);

    int pipe_fd1 = open(pipe1, O_WRONLY);
    write(pipe_fd1, buffer, count + 1);
    close(pipe_fd1);

    int pipe_fd2 = open(pipe2, O_RDONLY);
    ssize_t count2 = read(pipe_fd2, buffer, BUFF_SIZE);
    close(pipe_fd2);

    int file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (write(file, buffer, count2 - 1) != -1) {
        printf("Data written to output file successfully\n");
    } else {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }
    close(file);

    unlink(pipe1);
    unlink(pipe2);

    return EXIT_SUCCESS;
}