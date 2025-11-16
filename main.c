#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ToDo todo;

// Resolvi fazer um projeto com nextedLists para treinar conceitos de estrutras
// de dados :)

// Node que representa uma tarefa e contém um ponteiro para a próxima tarefa
struct ToDo {
    char title[100];
    todo *next;
    int index; // Número da tarefa
};

todo *start = NULL;
FILE *tasksFilePointer;

void welcomeUser();
void clearTerminal();
void getTodoList();
void createTodo();
void fixIndexes();
void deleteTodo(int desiredIndex);
void updateTodo(int desiredIndex);

int main() {
    int choice;
    int c;
    int desiredIndex;

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
            case 3:
                printf("\n Digite o número da tarefa que você deseja remover: ");
                scanf("%d", &desiredIndex);
                deleteTodo(desiredIndex);
                break;
            case 4:
                printf("\n Digite o número da tarefa que você deseja editar: ");
                scanf("%d", &desiredIndex);
                while ((c = getchar()) != '\n' && c != EOF);
                updateTodo(desiredIndex);
                break;
            case 5:
                getTodoList();
                exit(0);
                break;
            default:
                getTodoList();
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
        while (t->next != NULL) {
            t = t->next;
        }
        // Último nó agora aponta para o novo nó
        t->next = temp;
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

void deleteTodo(int desiredIndex) {
    todo *current, *previous = NULL;

    if (start == NULL) {
        printf("\nA lista de tarefas esta vazia.\n");
        return;
    }

    current = start;

    while (current != NULL && current->index != desiredIndex) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\nTarefa %d não encontrada.\n", desiredIndex);
        return;
    }

    if (previous == NULL) {
        // A tarefa a ser deletada é a primeira (start)
        start = current->next;
    } else {
        previous->next = current->next;
    }

    printf("\nTarefa %d removida com sucesso.\n", desiredIndex);
    free(current);
    
    fixIndexes();
}

void updateTodo(int desiredIndex) {
    todo *temp;
    char title[100];

    temp = start;

    printf("\n Digite o novo título da tarefa: ");
    fgets(title, sizeof(title), stdin);
    // Remove \n
    size_t len = strlen(title);
    if (len > 0 && title[len - 1] == '\n') {
        title[len - 1] = '\0';
    }

    while (temp->index != desiredIndex) {
        temp = temp->next;
    }
    
    strcpy(temp->title, title);
    return;
}

void getTodoList() {
    clearTerminal();
    todo *temp;
    temp = start;
    tasksFilePointer = fopen("tasks.txt", "w");

    if (tasksFilePointer == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    if (start == NULL) {
        printf("\nLista de tarefas vazia.\n");
        fprintf(tasksFilePointer, "Lista de tarefas vazia.\n");
        fclose(tasksFilePointer);
        return;
    }
    
    printf("\n--- Sua Lista de Tarefas ---\n");
    fprintf(tasksFilePointer, "--- Lista de Tarefas ---\n");
    while (temp != NULL) {
        printf("%d - ", temp->index);
        printf("%s\n", temp->title);
        
        fprintf(tasksFilePointer, "%d - ", temp->index);
        fprintf(tasksFilePointer, "%s\n", temp->title);
        temp = temp->next;
    }
    printf("----------------------------\n");
    fprintf(tasksFilePointer, "----------------------------\n");
    fclose(tasksFilePointer); 
    printf("\n(Lista salva em tasks.txt)\n");
}

void fixIndexes() {
    todo *temp;
    int i = 1;
    temp = start;
    while (temp != NULL) {
        temp->index = i;
        i++;
        temp = temp->next;
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