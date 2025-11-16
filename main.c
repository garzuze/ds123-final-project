#include <stdio.h>
#include <stlib.h>

typedef struct ToDo todo;

// Resolvi fazer um projeto com LinkedLists para treinar conceitos de estrutras
// de dados :)

// Node que representa uma tarefa e contém um ponteiro para a próxima tarefa
struct ToDo {
    char title[100];
    todo *link;
    int index; // Número da tarefa
};

todo * start = NULL;

