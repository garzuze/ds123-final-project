#include "todo.h"

todo *start = NULL;

void loadTodos() {
    FILE *tasksFilePointer;
    char line[256];
    char title[100];
    int index;
    todo *temp = NULL;

    tasksFilePointer = fopen("tasks.txt", "r");

    if (tasksFilePointer == NULL) {
        fclose(tasksFilePointer);
        return;
    }

    // Pula a primeira linha
    if (fgets(line, sizeof(line), tasksFilePointer) == NULL) {
        fclose(tasksFilePointer);
        return;
    }

    // Tenta ler as tarefas no formato que estão estruturadas no arquivo
    // Sempre adiciona um novo node ao último. Fluxo ideal: start == NULL 
    // na primeira iteração; vai adicionando os próximos ao start
    while (fscanf(tasksFilePointer, "%d - %[^\n]\n", &index, title) == 2) {
        todo *newNode = (todo *)calloc(1, sizeof(todo));
        strcpy(newNode->title, title);
        newNode->index = index;
        newNode->next = NULL;

        if (start == NULL) {
            start = newNode;
            temp = start;
        } else {
            temp->next = newNode;
            temp = newNode;
        }

    }
    fclose(tasksFilePointer);
    fixIndexes(); 
    printf("\n(Tarefas carregadas com sucesso!)\n");
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
    size_t len;

    temp = start;

    if (start == NULL) {
        printf("\nA lista está vazia. Não há tarefas para atualizar.\n");
        return;
    }
    
    while (temp != NULL && temp->index != desiredIndex) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nTarefa %d não encontrada.\n", desiredIndex);
        return;
    }

    printf("\n Digite o novo título da tarefa %d: ", desiredIndex);
    fgets(title, sizeof(title), stdin);
    
    // Remove \n
    len = strlen(title);
    if (len > 0 && title[len - 1] == '\n') {
        title[len - 1] = '\0';
    }

    if (strlen(title) > 0) {
        strcpy(temp->title, title);
        printf("\nTarefa %d atualizada com sucesso para: %s\n", desiredIndex, title);
        return;
    } else {
        printf("O título não pode ser vazio!\n");
        return;
    }
}

void getTodoList() {
    clearTerminal();
    FILE *tasksFilePointer;
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

void freeList() {
    todo *current = start;
    todo *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    start = NULL;
}

// Funções utilitárias

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
    printf("* Pressione Enter para começar!                      *\n");
    printf("* \n");
    printf("==================================================================\n\n");
    getchar();
    clearTerminal();
}