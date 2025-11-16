#include <stdio.h>
#include <stdlib.h>
#include "todo.h"

int main() {
    int choice;
    int c;
    int desiredIndex;

    welcomeUser();
    loadTodos();

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
                freeList();
                exit(0);
                break;
            default:
                getTodoList();
                printf("\nOpção não encontrada\n");
        }
    }
    return 0;
}

