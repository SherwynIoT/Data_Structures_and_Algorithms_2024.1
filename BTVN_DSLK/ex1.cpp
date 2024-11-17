#include <stdio.h>
#include <stdlib.h>

// Định nghĩa cấu trúc node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Hàm tạo node mới
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm node vào cuối danh sách
void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Hàm in danh sách
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Hàm xóa node đầu danh sách
void deleteHead(Node** head) {
    if (*head == NULL) {
        printf("Danh sách rỗng.\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Hàm xóa node cuối danh sách
void deleteTail(Node** head) {
    if (*head == NULL) {
        printf("Danh sách rỗng.\n");
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

// Hàm xóa node sau một node được chỉ định
void deleteAfterNode(Node* prevNode) {
    if (prevNode == NULL || prevNode->next == NULL) {
        printf("Không thể xóa node sau.\n");
        return;
    }
    Node* temp = prevNode->next;
    prevNode->next = temp->next;
    free(temp);
}

// Hàm chính để kiểm tra
int main() {
    Node* head = NULL;

    // Tạo danh sách
    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);

    printf("Danh sách ban đầu:\n");
    printList(head);

    // Xóa đầu danh sách
    printf("\nXóa đầu danh sách:\n");
    deleteHead(&head);
    printList(head);

    // Xóa cuối danh sách
    printf("\nXóa cuối danh sách:\n");
    deleteTail(&head);
    printList(head);

    // Xóa node sau node đầu tiên
    printf("\nXóa node sau node đầu tiên:\n");
    deleteAfterNode(head);
    printList(head);

    return 0;
}
