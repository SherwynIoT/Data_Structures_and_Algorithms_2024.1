#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* createNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->next = nullptr;
    return node;
}

Node* createCircularList(int N) {
    Node* head = createNode(1);
    Node* prev = head;
    for (int i = 2; i <= N; i++) {
        Node* node = createNode(i);
        prev->next = node;
        prev = node;
    }
    prev->next = head; // Tạo liên kết vòng
    return head;
}

int josephus(int N, int M) {
    if (N == 1) return 1;

    Node* head = createCircularList(N);
    Node* prev = nullptr;
    Node* current = head;
    
    // Lặp cho đến khi chỉ còn một người
    while (current->next != current) {
        // Di chuyển M-1 bước để tìm người bị loại
        for (int i = 1; i < M; i++) {
            prev = current; // Lưu lại người hiện tại vào biến prev
            current = current->next; // Di chuyển đến người tiếp theo
        }

        // Nếu M = 1, người bị loại là người hiện tại
        if (M == 1) {
            prev = current; // Lưu lại người hiện tại vào biến prev
            while (prev->next != current) { // Tìm người đứng trước người hiện tại
                prev = prev->next; // Di chuyển đến người tiếp theo
            }
        }

        // Loại bỏ người chơi hiện tại
        cout << "Người bị loại: " << current->data << endl; // In ra người bị loại
        prev->next = current->next; // Cập nhật liên kết để bỏ qua người bị loại
        delete current; // Giải phóng bộ nhớ của người bị loại
        current = prev->next; // Di chuyển đến người tiếp theo
    }
    
    int winner = current->data;
    delete current; // Xóa node cuối cùng
    return winner;
}

int main() {
    int N, M;
    cout << "Nhập số người chơi N: ";
    cin >> N;
    cout << "Nhập bước loại bỏ M: ";
    cin >> M;

    int winner = josephus(N, M);
    cout << "Người chiến thắng: " << winner << endl;

    return 0;
}