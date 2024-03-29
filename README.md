# Отчёт

## Рогатнев Дмитрий Александрович, БПИ229

## Вариант и условие задачи
Вариант: 5

Задание: Разработать программу, заменяющую все строчные гласные буквы
в заданной ASCII–строке заглавными.

## Тестовые файлы
Тест 1: Hello, World! This is a test file.\
Ответ 1: HEllO, WOrld! ThIs Is A tEst fIlE.

Тест 2: \
Ответ 2:

Тест 3: aeiouy\
Ответ 3: AEIOUY

Тест 4: bcdfghjklmnpqrstvwxyz\
Ответ 4: bcdfghjklmnpqrstvwxYz

Тест 5: HEllO, World! 1234567890 !!!!!!!!!!!!!!\
Ответ 5: HEllO, WOrld! 1234567890 !!!!!!!!!!!!!!

## Документация

Компиляция программы:
```console
gcc {mark}/main.c
```

Запуск программы:
```console
./a.out {input_file} {output_file}
```

# Оценка 4

## Условие задачи
Разработка программы, осуществляющей взаимодействие между тремя родственными процессами одной программы с использованием 
неименованных каналов.

## Схема

[Input file] -- (Process 1) -> [pipe] -- (Process 2) -> [pipe] -- (Process 3) -> [Exit file]

# Оценка 5

## Условие задачи
В дополнение к требованиям и программе на предыдущую
оценку необходимо разработать еще одну программу, в которой взаимодействие между тремя родственными процессами
одной программы осуществляется через именованные каналы.

## Схема

[Input file] -- (Process 1) -> [pipe1] -- (Process 2) -> [pipe2] -- (Process 3) -> [Exit file]

# Оценка 6

## Условие задачи
В дополнение к требованиям на предыдущую оценку разработать новую программу, которая осуществляет взаимодействие между 
двумя родственными процессами одной программы с использованием неименованных каналов

## Схема

[Input file] -- (Process 1) -> [pipe] -- (Process 2) -> [pipe] -- (Process 1) -> [Exit file]

# Оценка 7

## Условие задачи
В дополнение к требованиям на предыдущую оценку разработать программу, которая осуществляет взаимодействие между двумя 
родственными процессами одной программы с использованием именованных каналов

## Схема

[Input file] -- (Process 1) -> [pipe1] -- (Process 2) -> [pipe2] -- (Process 1) -> [Exit file]

# Оценка 8

## Условие задачи
В дополнение к требованиям на предыдущую оценку разработать программный продукт, в котором осуществляется взаимодействие 
между двумя независимыми процессами разных
программ с использованием именованных каналов

## Схема

[Input file] -- (Process 1) -> [pipe1] -- (Process 2) -> [pipe2] -- (Process 1) -> [Exit file]

## Запуск программы

Сначала переходим в [папку](8%2F) с программой.

### Сборка

```console
gcc transfer.c -o t.out
```

```console
gcc receiver.c -o r.out
```

### Запуск

```console
./t.out {input_file} {output_file}
```

```console
./r.out
```

# Оценка 9

## Условие задачи
В дополнение к требованиям на предыдущую оценку разработать программный продукт, в котором осуществляется взаимодействие
между двумя независимыми процессами разных
программ с использованием именованных каналов. Обмен данными ведется за счет многократной передачи текста через
ограниченные по размеру буферы.

## Схема

[Input file] -- (Process 1) -> [pipe1] -- (Process 2) -> [pipe2] -- (Process 3) -> [Exit file]

## Запуск программы

Сначала переходим в [папку](9%2F) с программой.

### Сборка

```console
gcc transfer.c -o t.out
```

```console
gcc receiver.c -o r.out
```

### Запуск

```console
./t.out {input_file} {output_file}
```

```console
./r.out
```

# Оценка 10

[10-й номер лежит в отдельном репозитории по этой ссылке](https://youtu.be/dQw4w9WgXcQ?si=xbUy1bKXEHjw7zXD)