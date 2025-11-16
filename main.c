#include <stdio.h>
#include <stdlib.h>

typedef struct ToDo todo;

// Resolvi fazer um projeto com LinkedLists para treinar conceitos de estrutras
// de dados :)

// Node que representa uma tarefa e contém um ponteiro para a próxima tarefa
struct ToDo {
    char title[100];
    todo *link;
    int index; // Número da tarefa
};

todo *start = NULL;

void welcomeUser();

int main() {
    int choice;
    welcomeUser();
}

void welcomeUser() {
    // Fonte inspirada no DOOM. Gerada no site:
    // https://patorjk.com/software/taag/#p=display&f=Doom&t=Bem+vindo%21&x=none&v=4&h=4&w=80&we=false
    printf("\n");
    printf("******************************************************************\n");
    printf("* \n");
    printf("* ______                         _           _       _             *\n");
    printf("* | ___ \\                       (_)         | |     | |            *\n");
    printf("* | |_/ / ___ _ __ ___    __   ___ _ __   __| | ___ | |            *\n");
    printf("* | ___ \\/ _ \\ '_ ` _ \\   \\ \\ / / | '_ \\ / _` |/ _ \\| |            *\n");
    printf("* | |_/ /  __/ | | | | |   \\ V /| | | | | (_| | (_) |_|            *\n");
    printf("* \\____/ \\___|_| |_| |_|    \\_/ |_|_| |_|\\__,_|\\___/(_)            *\n");
    printf("* \n");
    printf("******************************************************************\n");
    printf("* \n");
    printf("* AO SEU APLICATIVO DE TAREFAS!                      *\n");
    printf("* \n");
    printf("* Vamos organizar o seu dia!                         *\n");
    printf("* \n");
    printf("==================================================================\n\n");
}