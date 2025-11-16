#ifndef TODO_H
#define TODO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ToDo todo;

// Resolvi fazer um projeto com LinkedLists para treinar conceitos de estrutras
// de dados :)

// Node que representa uma tarefa e contém um ponteiro para a próxima tarefa
struct ToDo {
    char title[100];
    todo *next;
    int index; // Número da tarefa
};

extern todo *start;

void welcomeUser();
void clearTerminal();
void getTodoList();
void createTodo();
void fixIndexes();
void deleteTodo(int desiredIndex);
void updateTodo(int desiredIndex);
void freeList();
void loadTodos();

#endif // TODO_H