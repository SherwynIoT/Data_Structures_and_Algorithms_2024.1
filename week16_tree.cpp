#include <iostream>
#include <cstring> 

using namespace std;

// Cấu trúc cho một mục (node) trong cây
struct Node {
    char title[100];            // Tiêu đề (mảng ký tự)
    int pageCount;              // Số trang
    Node* firstChild;           // Con đầu tiên
    Node* nextSibling;          // Anh em tiếp theo

    Node(const char* t, int pages) : pageCount(pages), firstChild(nullptr), nextSibling(nullptr) {
        strcpy(title, t); // Sao chép chuỗi vào mảng ký tự
    }
};

// Hàm đếm số chương trong cuốn sách (chỉ các nút ở cấp đầu tiên)
int countChapters(Node* root) {
    int count = 0;
    Node* current = root;
    while (current) {
        count++;
        current = current->nextSibling;
    }
    return count;
}

// Hàm tìm chương dài nhất của cuốn sách
Node* findLongestChapter(Node* root) {
    Node* longest = nullptr;
    int maxPages = 0;
    Node* current = root;
    while (current) {
        if (current->pageCount > maxPages) {
            maxPages = current->pageCount;
            longest = current;
        }
        current = current->nextSibling;
    }
    return longest;
}

// Hàm tìm và xóa một mục (theo tiêu đề)
bool deleteSection(Node*& root, const char* title) {
    Node* prev = nullptr;
    Node* current = root;

    while (current) {
        if (strcmp(current->title, title) == 0) { // Tìm thấy mục cần xóa
            if (prev) {
                prev->nextSibling = current->nextSibling; // Bỏ qua nút hiện tại
            } else {
                root = current->nextSibling; // Xóa nút đầu tiên
            }

            // Xóa đệ quy các mục con
            Node* child = current->firstChild;
            while (child) {
                Node* temp = child;
                child = child->nextSibling;
                delete temp;
            }

            delete current; // Xóa nút hiện tại
            return true;
        }
        prev = current;
        current = current->nextSibling;
    }
    return false; // Không tìm thấy
}

// Hàm hiển thị cây mục lục (theo cấu trúc phân cấp)
void printTree(Node* root, int level = 0) {
    if (!root) return;
    for (int i = 0; i < level; i++) {
        cout << "  "; // In khoảng trắng để biểu thị cấp độ
    }
    cout << root->title << " (" << root->pageCount << " pages)" << endl;

    printTree(root->firstChild, level + 1); // In các mục con
    printTree(root->nextSibling, level);   // In các anh em
}

// Hàm thêm mục vào cây
void addSection(Node* parent, const char* title, int pages) {
    Node* newNode = new Node(title, pages);
    if (!parent->firstChild) {
        parent->firstChild = newNode; // Thêm vào con đầu tiên
    } else {
        Node* current = parent->firstChild;
        while (current->nextSibling) {
            current = current->nextSibling;
        }
        current->nextSibling = newNode; // Thêm vào danh sách anh em
    }
}

// Hàm chính
int main() {
    // Tạo gốc của cây
    Node* root = new Node("Book", 0);

    // Thêm các chương vào sách
    addSection(root, "Chapter 1", 10);
    addSection(root, "Chapter 2", 20);
    addSection(root, "Chapter 3", 15);

    // Thêm mục con vào Chapter 1
    addSection(root->firstChild, "Section 1.1", 5);
    addSection(root->firstChild, "Section 1.2", 7);

    // Thêm mục con vào Chapter 2
    addSection(root->firstChild->nextSibling, "Section 2.1", 8);

    // Hiển thị cây
    cout << "Book structure:" << endl;
    printTree(root);

    // Đếm số chương
    cout << "\nNumber of chapters: " << countChapters(root->firstChild) << endl;

    // Tìm chương dài nhất
    Node* longest = findLongestChapter(root->firstChild);
    if (longest) {
        cout << "Longest chapter: " << longest->title << " (" << longest->pageCount << " pages)" << endl;
    }

    // Xóa mục
    cout << "\nDeleting 'Chapter 2'..." << endl;
    if (deleteSection(root->firstChild, "Chapter 2")) {
        cout << "Chapter 2 deleted successfully." << endl;
    } else {
        cout << "Chapter 2 not found." << endl;
    }

    // Hiển thị lại cây
    cout << "\nUpdated book structure:" << endl;
    printTree(root);

    deleteSection(root, "Book"); // Xóa toàn bộ cây
    return 0;
}
