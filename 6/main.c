#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "../logic.h" // Заголовочный файл с функцией обработки строк

#define BUFF_SIZE 5000 // Определение размера буфера

int main(const int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pipe_fd1[2], pipe_fd2[2]; // Объявление файловых дескрипторов для двух неименованных каналов

    // Создание двух неименованных каналов
    if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }

    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd == -1) {
        perror("Error reading from input file");
        exit(EXIT_FAILURE);
    }
    printf("Input file read successfully\n");

    int pid1 = fork();
    if (pid1 == -1) {
        perror("pid1 failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        char buffer[BUFF_SIZE];

        ssize_t count = read(file_fd, buffer, BUFF_SIZE);
        close(file_fd);

        write(pipe_fd1[1], buffer, count + 1);
        close(pipe_fd1[1]);

        ssize_t count2 = read(pipe_fd2[0], buffer, BUFF_SIZE);
        close(pipe_fd2[0]);

        int file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

        if (write(file, buffer, count2 - 1) != -1) {
            printf("Data written to output file successfully\n");
        } else {
            perror("Error writing to file");
            exit(EXIT_FAILURE);
        }
        close(file);

        exit(EXIT_SUCCESS);
    } else {
        char buffer[BUFF_SIZE];
        close(pipe_fd1[1]);
        close(pipe_fd2[0]);

        ssize_t count = read(pipe_fd1[0], buffer, BUFF_SIZE);
        close(pipe_fd1[0]);

        printf("Starting processing data...\n");
        edit_str(buffer);
        printf("Data processed successfully\n");

        write(pipe_fd2[1], buffer, count);
        close(pipe_fd2[1]);

        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}