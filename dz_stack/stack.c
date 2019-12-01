#include "stdio.h"
#include "stdlib.h"

typedef struct stackNode {
        char fio[64];
        char phoneNumber[32];
        struct stackNode *next;
} Node;

int showMenu(int *menuChoosedItemPtr) {
        printf( "\n\rChoose action:\n\r" );
        printf( "1. Push element\n\r" );
        printf( "2. Pop element\n\r" );
        printf( "3. List(pop all)\n\r" );
        printf( "4. Exit\n\n\r>>" );
        scanf("%d", menuChoosedItemPtr);
        return 0;
}

int push(Node **topPtr) {
        Node *newNode = (Node*) malloc(sizeof(Node));
        printf("\n\rInput abonent fio for push in stack:\n\r>>");
        scanf(" %63[^\n]s", newNode->fio);
        printf("Input abonent phone number for push in stack:\n\r>>");
        scanf(" %31[^\n]s", newNode->phoneNumber);
        newNode->next = *topPtr;
        *topPtr = newNode;
        return 0;
}

int pop(Node **topPtr) {
        if (*topPtr == NULL){
                printf("Stack is empty!!!\n\r");
        }else{
                Node *cur = *topPtr;
                *topPtr = (*topPtr)->next;
                printf("%s %s\n\r", cur->fio, cur->phoneNumber);
                free(cur);
        }
        return 0;
}

int list(Node **topPtr){
        do{
                pop(topPtr);
        }while (*topPtr != NULL);
        return 0;
}

int main () {
        Node *stackPtr = NULL;
        int doProgram = 0;
        int choosedParameter = 4;
        while(doProgram == 0){
                showMenu(&choosedParameter);
                switch(choosedParameter) {
                        case 1:
                                {
                                doProgram = push(&stackPtr);
                                break;
                                }
                        case 2:
                                {
                                printf("\n\r");
                                doProgram = pop(&stackPtr);
                                break;
                                }
                        case 3:
                                {
                                printf("\n\r");
                                doProgram = list(&stackPtr);
                                break;
                                }
                        case 4:
                                {
                                doProgram = 1;
                                break;
                                }
                        default:
                                printf("Invalid entered menu option. It should be 1-4...\n\r");
                }
        }
        return 0;
}
