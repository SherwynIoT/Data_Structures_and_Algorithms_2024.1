#include <stdio.h>    // Thư viện chuẩn cho các hàm nhập/xuất
#include <stdlib.h>   // Thư viện chuẩn cho cấp phát bộ nhớ động
#include <string.h>   // Thư viện hỗ trợ thao tác với chuỗi

// Định nghĩa cấu trúc node trong danh sách liên kết
typedef struct Node {
    char word[50];       // Mỗi từ được lưu trong một node với độ dài tối đa 50 ký tự
    struct Node* next;   // Con trỏ trỏ đến node tiếp theo trong danh sách liên kết
} Node;

// Hàm khởi tạo một node mới với từ được truyền vào
Node* createNode(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Cấp phát bộ nhớ cho node mới
    strcpy(newNode->word, word);                  // Sao chép từ vào thuộc tính word của node
    newNode->next = NULL;                         // Đặt con trỏ next của node này là NULL (vì đây là node cuối)
    return newNode;                               // Trả về con trỏ đến node mới
}

// Hàm thêm một node vào cuối danh sách liên kết
void appendNode(Node** head, char* word) {
    Node* newNode = createNode(word);            // Tạo một node mới với từ được truyền vào
    if (*head == NULL) {                         // Kiểm tra nếu danh sách hiện đang rỗng
        *head = newNode;                         // Đặt node mới là đầu danh sách nếu danh sách rỗng
    } else {                                     // Nếu danh sách không rỗng
        Node* temp = *head;                      // Khởi tạo con trỏ tạm để duyệt danh sách từ đầu
        while (temp->next != NULL) {             // Duyệt đến cuối danh sách
            temp = temp->next;                   // Di chuyển đến node tiếp theo
        }
        temp->next = newNode;                    // Thêm node mới vào cuối danh sách
    }
}

// Hàm đếm số từ trong danh sách liên kết
int countWords(Node* head) {
    int count = 0;                               // Khởi tạo biến đếm
    Node* temp = head;                           // Con trỏ tạm để duyệt danh sách từ đầu
    while (temp != NULL) {                       // Duyệt qua từng node cho đến khi hết danh sách
        count++;                                 // Tăng biến đếm lên 1 cho mỗi node
        temp = temp->next;                       // Di chuyển đến node tiếp theo
    }
    return count;                                // Trả về tổng số từ đếm được
}

// Hàm tìm từ xuất hiện nhiều nhất trong danh sách
void findMostFrequentWord(Node* head) {
    Node* temp1 = head;                          // Con trỏ để duyệt qua từng từ
    int maxCount = 0;                            // Biến lưu số lần xuất hiện nhiều nhất của một từ
    char maxWord[50];                            // Mảng để lưu từ xuất hiện nhiều nhất
    
    while (temp1 != NULL) {                      // Duyệt qua từng node trong danh sách
        int count = 1;                           // Khởi tạo biến đếm cho từ hiện tại
        Node* temp2 = temp1->next;               // Con trỏ duyệt qua các từ tiếp theo để so sánh
        while (temp2 != NULL) {                  // So sánh từ hiện tại với các từ sau nó
            if (strcmp(temp1->word, temp2->word) == 0) {  // Nếu từ trùng nhau
                count++;                         // Tăng biến đếm nếu trùng từ
            }
            temp2 = temp2->next;                 // Di chuyển đến node tiếp theo
        }
        
        if (count > maxCount) {                  // Kiểm tra nếu số lần xuất hiện của từ lớn hơn maxCount
            maxCount = count;                    // Cập nhật maxCount
            strcpy(maxWord, temp1->word);        // Cập nhật maxWord với từ có số lần xuất hiện nhiều nhất
        }
        temp1 = temp1->next;                     // Di chuyển đến từ tiếp theo trong danh sách
    }
    
    printf("Từ xuất hiện nhiều nhất là '%s' với số lần xuất hiện là %d\n", maxWord, maxCount);  // In kết quả
}

// Hàm loại bỏ từ láy (từ có cấu trúc hai từ giống nhau liên tiếp, ví dụ: "xanh xanh")
void removeRedundantWords(Node* head) {
    Node* temp = head;                           // Con trỏ tạm để duyệt danh sách
    while (temp != NULL && temp->next != NULL) { // Duyệt đến cuối danh sách, trừ node cuối
        if (strcmp(temp->word, temp->next->word) == 0) {  // Kiểm tra nếu từ trùng với từ tiếp theo
            Node* redundantNode = temp->next;    // Lưu node cần xóa
            temp->next = temp->next->next;       // Bỏ qua node cần xóa
            free(redundantNode);                 // Giải phóng bộ nhớ cho node vừa bỏ qua
        }
        temp = temp->next;                       // Di chuyển đến node tiếp theo
    }
}

// Hàm in các từ trong danh sách liên kết
void printList(Node* head) {
    Node* temp = head;                           // Con trỏ tạm để duyệt danh sách từ đầu
    while (temp != NULL) {                       // Duyệt qua từng node trong danh sách
        printf("%s ", temp->word);               // In từ của mỗi node
        temp = temp->next;                       // Di chuyển đến node tiếp theo
    }
    printf("\n");                                // Xuống dòng sau khi in hết danh sách
}

int main() {
    Node* head = NULL;                           // Khởi tạo danh sách liên kết trống
    char input[500];                             // Mảng để lưu chuỗi nhập từ người dùng

    // Nhập một câu từ người dùng
    printf("Enter a sentence: ");
    fgets(input, 500, stdin);                    // Đọc chuỗi từ người dùng (tối đa 500 ký tự)
    input[strcspn(input, "\n")] = '\0';          // Loại bỏ ký tự xuống dòng nếu có

    // Phân tách câu thành các từ và thêm vào danh sách liên kết
    char* token = strtok(input, " ");            // Tách từ đầu tiên trong chuỗi
    while (token != NULL) {                      // Lặp lại cho đến khi hết các từ
        appendNode(&head, token);                // Thêm từ vào cuối danh sách liên kết
        token = strtok(NULL, " ");               // Lấy từ tiếp theo trong chuỗi
    }

    printf("List of words before removing duplicates:\n");
    printList(head);                             // In danh sách từ trước khi loại bỏ từ láy

    // Loại bỏ từ láy
    removeRedundantWords(head);
    printf("List of words after removing duplicates:\n");
    printList(head);                             // In danh sách từ sau khi loại bỏ từ láy

    // Đếm số từ
    int wordCount = countWords(head);
    printf("The number of words in the sentence: %d\n", wordCount);  // In số từ trong danh sách

    // Tìm từ xuất hiện nhiều nhất
    findMostFrequentWord(head);                  // In từ xuất hiện nhiều nhất

    return 0;
}
