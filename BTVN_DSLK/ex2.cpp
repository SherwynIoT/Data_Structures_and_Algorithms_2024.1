#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cấu trúc lưu thông tin file
typedef struct File {
    char name[50];
    int size;         // Dung lượng (KB)
    int saveTime;     // Thời gian lưu (giả sử đơn vị: ngày)
} File;

// Hàm in danh sách file
void printFiles(File files[], int n) {
    printf("Danh sách file:\n");
    for (int i = 0; i < n; i++) {
        printf("File: %s, Size: %d KB, SaveTime: %d days\n", files[i].name, files[i].size, files[i].saveTime);
    }
    printf("\n");
}

// Hàm sắp xếp file theo dung lượng tăng dần (dùng Bubble Sort)
void sortFilesBySize(File files[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (files[j].size > files[j + 1].size || 
                (files[j].size == files[j + 1].size && files[j].saveTime > files[j + 1].saveTime)) {
                // Hoán đổi nếu dung lượng lớn hơn hoặc dung lượng bằng nhưng thời gian lâu hơn
                File temp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = temp;
            }
        }
    }
}

// Hàm xóa các file có dung lượng bé nhất và thời gian lưu lâu nhất
int deleteSmallestFiles(File files[], int *n) {
    if (*n == 0) return 0;

    int minSize = files[0].size;
    int i = 0, deletedCount = 0;

    while (i < *n) {
        if (files[i].size == minSize) {
            printf("Xóa file: %s, Size: %d KB, SaveTime: %d days\n", files[i].name, files[i].size, files[i].saveTime);

            // Dịch các file sau vị trí i lên một bậc
            for (int j = i; j < *n - 1; j++) {
                files[j] = files[j + 1];
            }
            (*n)--;
            deletedCount++;
        } else {
            i++;
        }
    }

    return deletedCount;
}

int main() {
    // Khởi tạo danh sách file
    File files[] = {
        {"file1.txt", 500, 20},
        {"file2.txt", 300, 50},
        {"file3.txt", 300, 10},
        {"file4.txt", 800, 5},
        {"file5.txt", 300, 40}
    };
    int n = sizeof(files) / sizeof(files[0]);

    printf("Danh sách file ban đầu:\n");
    printFiles(files, n);

    // Sắp xếp file theo dung lượng tăng dần và thời gian lưu
    sortFilesBySize(files, n);

    printf("Danh sách file sau khi sắp xếp:\n");
    printFiles(files, n);

    // Xóa các file có dung lượng bé nhất và thời gian lưu lâu nhất
    printf("Xóa các file có dung lượng bé nhất và thời gian lưu lâu nhất:\n");
    deleteSmallestFiles(files, &n);

    printf("\nDanh sách file sau khi xóa:\n");
    printFiles(files, n);

    return 0;
}
