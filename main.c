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
void createTodo();
void fixIndexes();

int main() {
    int choice;
    int c;
    welcomeUser();
    while (1) {
        printf("\n 1 - Ver sua lista de tarefas;");
        printf("\n 2 - Criar uma tarefa;");
        printf("\n 3 - Deletar uma tarefa;");
        printf("\n 4 - Atualizar uma tarefa;");
        printf("\n 5 - Sair;");
        printf("\n\n Digite sua escolha: ");
        scanf("%d", &choice);
        // Limpa o buffer de entrada para remover \n
        while ((c = getchar()) != '\n' && c != EOF);
        switch(choice) {
            case 1:
                getTodoList();
                break;
            case 2:
                createTodo();
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("\nOpção não encontrada\n");
        }
    }
    return 0;
}

void createTodo() {
    todo *t, *temp;
    char choice;
    char c;
    clearTerminal();
    
    temp = (todo *)calloc(1, sizeof(todo));
    printf("\n Digite a tarefa: ");
    fgets(temp->title, sizeof(temp->title), stdin);
    // Remove \n
    size_t len = strlen(temp->title);
    if (len > 0 && temp->title[len - 1] == '\n') {
        temp->title[len - 1] = '\0';
    }
    
    if (start == NULL) {
        // Primeira tarefa: o start aponta para o novo nó
        start = temp;
    } else {
        t = start;
        while (t->link != NULL) {
            t = t->link;
        }
        // Último nó agora aponta para o novo nó
        t->link = temp;
    }
    fixIndexes();
    
    printf("Quer adicionar mais uma tarefa? (s/n): ");
    choice = getchar();
    while ((c = getchar()) != '\n' && c != EOF);
    clearTerminal();
    if (choice == 's') {
        createTodo();
    } else {
        return;
    }
}

void getTodoList() {
    clearTerminal();
    todo *temp;
    temp = start;
    if (start == NULL) {
        printf("\nLista de tarefas vazia.\n");
        return;
    }
    
    printf("\n--- Sua Lista de Tarefas ---\n");
    while (temp != NULL) {
        printf("%d - ", temp->index);
        printf("%s\n", temp->title);
        temp = temp->link;
    }
    printf("----------------------------\n");
}

void fixIndexes() {
    todo *temp;
    int i = 1;
    temp = start;
    while (temp != NULL) {
        temp->index = i;
        i++;
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