#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void clearTerminal();
void getTodoList();

int main() {
    int choice;
    welcomeUser();
    todo *t;

    t = (todo *)calloc(1, sizeof(todo));
    start = t;
    strcpy(t->title, "Teste");
    t->index = 1;
    start->link = NULL;
    while (1) {
        printf("\n 1 - Ver sua lista de tarefas;");
        printf("\n 2 - Criar uma tarefa;");
        printf("\n 3 - Deletar uma tarefa;");
        printf("\n 4 - Atualizar uma tarefa;");
        printf("\n 5 - Sair;");
        printf("\n\n Digite sua escolha: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                getTodoList();
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("\nOpção não encontrada\n");
        }
    }
}

void getTodoList() {
    clearTerminal();
    todo *temp;
    temp = start;
    if (start == NULL) {
        printf("\nLista de tarefas vazia.\n");
    }

    while (temp != NULL) {
        printf("%d - ", temp->index);
        printf("%s\n", temp->title);
        temp = temp->link;
    }
}

void clearTerminal() {
    printf("\033[2J");
    printf("\033[H");
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
    getchar();
    clearTerminal();
}