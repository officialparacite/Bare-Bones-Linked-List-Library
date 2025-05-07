#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node* next;
}Node;

Node* insertAtHead(Node* head, int value);
Node* insertAtTail(Node* head, int value);
Node* deleteAtHead(Node* head);
Node* deleteAtTail(Node* head);
void printList(Node* head);
void freeList(Node* head);
int recursiveLength(Node* node);
int findFirstMatch(Node* node, int value);
int countMatches(Node* node, int value);
void replaceMatches(Node* node, int value, int replace);
Node* deleteFirstMatch(Node* head, int value, bool* was_deleted);
Node* deleteMatches(Node* head, int value, int* deleted);
Node* append_list(Node* head1, Node* head2);
Node* reverse_list(Node* head);
void bubble_sort(Node* head);
void delete_duplicates(Node* head);
void delete_duplicates_sorted(Node* head);
Node* insertAfter(Node* head, int target_value, int new_value);

int main (int argc, char* argv[]){
    Node* list1_head = NULL, *list2_head = NULL;
    for (int i = 0; i < 5; i++){
        list1_head = insertAtTail(list1_head, i);
    }
    for (int i = 5; i < 10; i++){
        list2_head = insertAtTail(list2_head, i);
    }

    printList(list1_head);
    printList(list2_head);

    Node* list3_head = reverse_list(list1_head);
    Node* list4_head = reverse_list(list2_head);

    printList(list3_head);
    printList(list4_head);

    freeList(list1_head);
    freeList(list2_head);

    return 0;
}

Node* insertAtHead(Node* head, int value){
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Allocation Failed\n");
        return head;
    }
    newNode->value = value;
    if (head == NULL) {
        newNode->next = NULL;
        return newNode;
    }
    newNode->next = head;
    return newNode;
}
Node* insertAtTail(Node* head, int value){
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        printf("Allocation Failed\n");
        return head;
    }
    newNode->value = value;
    if (head == NULL){
        newNode->next = NULL;
        return newNode;
    }
    Node* current = head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
    newNode->next = NULL;
    return head;
}
void printList(Node* head){
    if (head == NULL){
        printf("List is empty");
        return;
    }
    Node* current = head;
    while(current != NULL){
        printf("[%d] -> ", current->value);
        current = current->next;
    }
    printf("[node_len: %d]", recursiveLength(head));
    printf("\n");
}
void freeList(Node* head){
    Node* current = head;
    Node* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}
Node* deleteAtHead(Node* head){
    if (head == NULL) return NULL;
    Node* newhead = head->next;
    free(head);
    return newhead;
}
Node* deleteAtTail(Node* head){
    if (head == NULL) return NULL;
    if (head->next == NULL){
        free(head);
        return NULL;
    }
    Node* current = head;
    Node* previous = NULL;

    while (current->next != NULL){
        previous = current;
        current = current->next;
    }
    previous->next = NULL;
    free(current);
    return head;
}
int recursiveLength(Node* node){
    if (node == NULL) return 0;
    return 1 + recursiveLength(node->next);
}
int findFirstMatch(Node* node, int value){
    if (node == NULL) return 0;
    else if (node->value == value) return 1;
    return findFirstMatch(node->next, value);
}
int countMatches(Node* node, int value){
    if (node == NULL) return 0;
    else if (node->value == value) return 1 + countMatches(node->next, value);
    return countMatches(node->next, value);
}
void replaceMatches(Node* node, int value, int replace){
    if (node == NULL) return;
    else if (node->value == value){
        node->value = replace;
    }
    return replaceMatches(node->next, value, replace);
}
Node* deleteFirstMatch(Node* head, int value, bool* was_deleted){
    if (head == NULL) return NULL;
    if (head->value == value){
        Node* temp = head->next;
        free(head);
        *was_deleted = true;
        return temp->next;
    }
    Node* current = head->next;
    Node* prev = head;
    while (current != NULL) {
        if (current->value == value){
            prev->next = current->next;
            free(current);
            *was_deleted = true;
            return head;
        }
        prev = current;
        current = current->next;
    }
    *was_deleted = false;
    return head;
}

Node* deleteMatches(Node* head, int value, int* deleted) {
    *deleted = 0;
    Node* current = head;
    Node* temp = NULL;

    while (current != NULL && current->value == value) {
        temp = current;
        current = current->next;
        free(temp);
        (*deleted)++;
    }

    if (current == NULL) return NULL;

    Node* new_head = current;
    Node* prev = current;
    current = current->next;

    while (current != NULL) {
        if (current->value == value) {
            temp = current;
            prev->next = current->next;
            current = current->next;
            free(temp);
            (*deleted)++;
        } else {
            prev = current;
            current = current->next;
        }
    }
    return new_head;
}
Node* append_list(Node* head1, Node* head2){
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    Node* current = head1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = head2;
    return head1;
}
Node* reverse_list(Node* head){
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
void bubble_sort(Node* head){
    if (head == NULL) return;
    if (head->next == NULL) return;

    bool swapped = false;
    do{
        swapped = false;
        Node* current = head;
        Node* prev = NULL;

        while(current->next != NULL){
            prev = current;
            current = current->next;
            if (current->value < prev->value){
                int temp = prev->value;
                prev->value = current->value;
                current->value = temp;
                swapped = true;
            } 
        }
    }while(swapped);
}
void delete_duplicates(Node* head) {
    if (head == NULL || head->next == NULL) return;

    Node* current1 = head;
    while (current1 != NULL && current1->next != NULL) {
        Node* current2 = current1;
        while (current2->next != NULL) {
            if (current1->value == current2->next->value) {
                Node* duplicate = current2->next;
                current2->next = current2->next->next;
                free(duplicate);
            } else {
                current2 = current2->next;
            }
        }
        current1 = current1->next;
    }
}
void delete_duplicates_sorted(Node* head) {
    if (head == NULL || head->next == NULL) return;

    Node* current = head;
    while (current != NULL && current->next != NULL) {
        if (current->value == current->next->value) {
            Node* duplicate = current->next;
            current->next = current->next->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
}
Node* insertAfter(Node* head, int target_value, int new_value){
    Node* new_node = calloc(1, sizeof(Node));
    new_node->value = new_value;

    if(head == NULL) return new_node;

    Node* current = head;
    while (current != NULL) {
        if (current->value == target_value) {
            new_node->next = current->next;
            current->next = new_node;
            return head;
        }
        current = current->next;
    }

    free(new_node);
    return head;
}

