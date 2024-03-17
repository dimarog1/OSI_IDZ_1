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
    int pid1, pid2; // Объявление переменных для идентификаторов процессов

    // Создание двух неименованных каналов
    if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1) {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    } else {
        printf("Pipes created successfully\n");
    }

    // Открытие файла для чтения
    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd == -1) {
        perror("Error reading from input file");
        exit(EXIT_FAILURE);
    }
    printf("Input file read successfully\n");

    // Создание первого дочернего процесса
    pid1 = fork();
    if (pid1 == -1) {
        perror("pid1 failed");
        exit(EXIT_FAILURE);
    }

    // В первом дочернем процессе
    if (pid1 == 0) {
        char buffer[BUFF_SIZE]; // Буфер для чтения данных из файла

        // Чтение данных из файла в буфер
        ssize_t count = read(file_fd, buffer, BUFF_SIZE);
        close(file_fd); // Закрытие файла

        // Запись данных из буфера в первый канал
        write(pipe_fd1[1], buffer, count + 1);
        close(pipe_fd1[1]); // Закрытие записывающего конца первого канала

        exit(EXIT_SUCCESS); // Завершение первого дочернего процесса
    }

    // Создание второго дочернего процесса
    pid2 = fork();
    if (pid2 == -1) {
        perror("pid2 failed");
        exit(EXIT_FAILURE);
    }

    // Во втором дочернем процессе
    if (pid2 == 0) {
        char buffer[BUFF_SIZE]; // Буфер для чтения данных из первого канала

        // Чтение данных из первого канала в буфер
        ssize_t count = read(pipe_fd1[0], buffer, BUFF_SIZE);
        close(pipe_fd1[0]); // Закрытие читающего конца первого канала

        // Обработка данных
        printf("Starting processing data...\n");
        edit_str(buffer); // Вызов функции обработки данных
        // Запись обработанных данных во второй канал
        write(pipe_fd2[1], buffer, count);
        printf("Data processed successfully\n");

        close(pipe_fd2[1]); // Закрытие записывающего конца второго канала

        exit(EXIT_SUCCESS); // Завершение второго дочернего процесса
    }

    // В родительском процессе
    char buffer[BUFF_SIZE]; // Буфер для чтения данных из второго канала

    // Чтение данных из второго канала в буфер
    ssize_t count = read(pipe_fd2[0], buffer, BUFF_SIZE);
    close(pipe_fd2[0]); // Закрытие читающего конца второго канала

    // Открытие файла для записи
    int file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    // Запись данных из буфера в файл
    if (write(file, buffer, count - 1) != -1) {
        printf("Data written to output file successfully\n");
    } else {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }
    close(file); // Закрытие файла

    return EXIT_SUCCESS; // Завершение родительского процесса
}