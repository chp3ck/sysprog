#include "stdio.h"
#include "stdlib.h"

typedef struct ringListNode {
        struct ringListNode *prev;
        char data[128];
        struct ringListNode *next;
} Node;

int showMenu(int *menuChoosedItemPtr) {
        printf("\n\rChoose action:\n\r");
        printf("1. Push element\n\r");
        printf("2. Pop current element\n\r");
        printf("3. List&check length\n\r");
        printf("4. Move to previous\n\r");
        printf("5. Move to next\n\r");
        printf("6. Exit\n\n\r>>");
        scanf("%d", menuChoosedItemPtr);
        return 0;
}

int push(Node **curPtr) {
        Node *newNode = (Node*) malloc(sizeof(Node));
        printf("Input data for push in new element of the list:\n\r>>");
        scanf(" %127[^\n]s", newNode->data);
        if (*curPtr == NULL){
                newNode->prev = newNode;
                newNode->next = newNode;
                *curPtr = newNode;
        }else{
                newNode->prev = *curPtr;
                newNode->next = (*curPtr)->next;
                (*curPtr)->next = newNode;
                (newNode->next)->prev = newNode;
                *curPtr = newNode;
        }
        return 0;
}

int pop(Node **curPtr) {
        if (*curPtr == NULL){
                printf("List is empty!!!\n\r");
        }else if (((*curPtr)->prev) == *curPtr){
                printf("Popped element: %s\n\r", (*curPtr)->data);
                free(*curPtr);
                *curPtr = NULL;
		printf("List is empty!!!\n\r");
        }else{
                Node *cur = *curPtr;
                (cur->prev)->next = cur->next;
                (cur->next)->prev = cur->prev;
                printf("Popped element: %s\n\r", cur->data);
                *curPtr = cur->next;
                free(cur);
		printf("Сurrent element: %s\n\r", (*curPtr)->data);
        }
        return 0;
}

int list(Node **curPtr, int *listLengthPtr){
        Node *startPtr = *curPtr;
        *listLengthPtr = 0;
        if(*curPtr == NULL){
                printf("List is empty!!!\n\r");
        }else{
                printf("Current: ");
                do{
                        printf("%s\n\r", (*curPtr)->data);
                        (*listLengthPtr)++;
                        *curPtr = (*curPtr)->next;
                }while (*curPtr != startPtr);
        }
        printf("List length: %d\n\r", *listLengthPtr);
        return 0;
}

int prev(Node **curPtr){
        if (*curPtr == NULL){
                printf("List is empty!!!\n\r");
        }else{
                *curPtr = (*curPtr)->prev;
                printf("Current element: %s\n\r", (*curPtr)->data);
        }
        return 0;
}

int next(Node **curPtr){
        if (*curPtr == NULL){
                printf("List is empty!!!\n\r");
        }else{
                *curPtr = (*curPtr)->next;
                printf("Current element: %s\n\r", (*curPtr)->data);
        }
        return 0;
}

int exit_ringlist(Node **curPtr){
        if (*curPtr != NULL){
                if (((*curPtr)->prev) == *curPtr){
                        free(*curPtr);
                }else{
                        Node *cur = NULL;
                        do{
                                cur = *curPtr;
                                *curPtr = (*curPtr)->next;
                                (cur->prev)->next = cur->next;
                                (cur->next)->prev = cur->prev;
                                free(cur);
                        }while(cur != *curPtr);
                }
        }
        return 1;
}

int main () {
        Node *currentListPtr = NULL;
        int doProgram = 0;
        int choosedParameter = 6;
        int listLength = 0;
        while(doProgram == 0){
                showMenu(&choosedParameter);
                printf("\n\r");
                switch(choosedParameter) {
                        case 1:
                                {
                                doProgram = push(&currentListPtr);
                                break;
                                }
                        case 2:
                                {
                                doProgram = pop(&currentListPtr);
                                break;
                                }
                        case 3:
                                {
                                doProgram = list(&currentListPtr, &listLength);
                                break;
                                }
                        case 4:
                                {
                                doProgram = prev(&currentListPtr);
                                break;
                                }
                        case 5:
                                {
                                doProgram = next(&currentListPtr);
                                break;
                                }
                        case 6:
                                {
                                doProgram = exit_ringlist(&currentListPtr);
                                break;
                                }
                        default:
                                printf("Invalid entered menu option. It should be 1-6...\n\r");
                }
        }
        return 0;
}
