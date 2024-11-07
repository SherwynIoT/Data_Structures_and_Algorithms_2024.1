#include <iostream> 

using namespace std;  

// Định nghĩa cấu trúc Ngay để lưu trữ ngày, tháng, năm sinh của sinh viên
struct Ngay
{
    int ngay, thang, nam;
};

// Định nghĩa cấu trúc SinhVien để lưu thông tin của sinh viên
struct SinhVien
{
    char maSV[10];      // Mã sinh viên
    char hoTen[50];     // Họ và tên sinh viên
    int gioiTinh;       // Giới tính 
    Ngay ngaySinh;      // Ngày sinh
    char diaChi[100];   // Địa chỉ sinh viên
    char lop[12];       // Lớp học
    char khoa[7];       // Khoa
};

// Định nghĩa cấu trúc Node để tạo các nút của danh sách liên kết
struct Node
{
    SinhVien data;  // Dữ liệu của mỗi nút là một sinh viên
    Node *next;     // Con trỏ trỏ đến nút kế tiếp
};

// Định nghĩa cấu trúc List để lưu trữ danh sách các sinh viên
struct List
{
    Node *first;    // Con trỏ đầu danh sách
    Node *last;     // Con trỏ cuối danh sách
};

// Khởi tạo danh sách rỗng
void initList(List &list)
{
    list.first = list.last = nullptr;  // Cả đầu và cuối danh sách đều là nullptr
}

// Tạo một nút mới với dữ liệu sinh viên
Node *createNode(SinhVien sv)
{
    Node *p = new Node;     // Cấp phát bộ nhớ cho nút mới
    p->data = sv;           // Gán dữ liệu sinh viên cho nút
    p->next = nullptr;      // Đặt nút tiếp theo là nullptr
    return p;               // Trả về nút vừa tạo
}

// Hàm so sánh hai chuỗi ký tự
int compareStrings(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))  // Lặp cho đến khi hết chuỗi hoặc gặp ký tự khác nhau
    {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;  // Trả về sự khác biệt giữa hai ký tự
}

// Hàm chèn một nút vào danh sách theo thứ tự tăng dần mã sinh viên
void insertNode(List &list, SinhVien sv)
{
    Node *p = createNode(sv);  // Tạo nút mới với sinh viên sv
    if (list.first == nullptr || compareStrings(list.first->data.maSV, sv.maSV) > 0)  // Kiểm tra nếu danh sách rỗng hoặc sv có mã nhỏ nhất
    {
        p->next = list.first;  // Chèn nút vào đầu danh sách
        list.first = p;
        if (list.last == nullptr)
            list.last = p;      // Nếu danh sách rỗng thì cập nhật con trỏ last
    }
    else
    {
        Node *temp = list.first;
        while (temp->next != nullptr && compareStrings(temp->next->data.maSV, sv.maSV) < 0)  // Tìm vị trí chèn
        {
            temp = temp->next;
        }
        p->next = temp->next;   // Chèn nút p sau temp
        temp->next = p;

        if (p->next == nullptr)  // Cập nhật last nếu chèn vào cuối danh sách
            list.last = p;
    }
}

// Hàm nhập thông tin sinh viên
void nhapSinhVien(SinhVien &sv)
{
    cout << "Nhap ma sinh vien: ";
    cin.getline(sv.maSV, 10);   // Nhập mã sinh viên
    
    cout << "Nhap ho ten: ";
    cin.getline(sv.hoTen, 50);  // Nhập họ tên sinh viên
    
    cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
    cin >> sv.gioiTinh;         // Nhập giới tính
    cin.ignore();               // Xóa ký tự xuống dòng trong bộ đệm
    
    cout << "Nhap ngay sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;  // Nhập ngày, tháng, năm sinh
    cin.ignore();
    
    cout << "Nhap dia chi: ";
    cin.getline(sv.diaChi, 100);    // Nhập địa chỉ
    
    cout << "Nhap lop: ";
    cin.getline(sv.lop, 12);        // Nhập lớp học
    
    cout << "Nhap khoa: ";
    cin.getline(sv.khoa, 7);        // Nhập khoa
}

// Hàm nhập danh sách sinh viên
void nhapListSV(List &list)
{
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;               // Nhập số lượng sinh viên
    cin.ignore();
    for (int i = 0; i < n; i++)  // Vòng lặp nhập từng sinh viên
    {
        SinhVien sv;
        cout << "Nhap thong tin cho sinh vien thu " << i + 1 << ":" << endl;
        nhapSinhVien(sv);         // Nhập thông tin sinh viên
        insertNode(list, sv);     // Chèn sinh viên vào danh sách
    }
}

// Hàm in danh sách sinh viên
void printList(const List &list)
{
    Node *p = list.first;
    while (p != nullptr)      // Lặp qua các nút trong danh sách
    {
        cout << "Ma SV: " << p->data.maSV << endl;
        cout << "Ho ten: " << p->data.hoTen  << endl;
        cout << "Gioi tinh: " << (p->data.gioiTinh ? "Nam" : "Nu") << endl;
        cout << "Ngay sinh: " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
        cout << "Dia chi: " << p->data.diaChi << endl;
        cout << "Lop: " << p->data.lop << endl;
        cout << "Khoa: " << p->data.khoa << endl;
        cout << endl;
        p = p->next;          // Chuyển sang nút tiếp theo
    }
}

// Hàm tìm và in sinh viên có ngày sinh giống nhau
void StudentsWithSameBirthday(const List &list, const Ngay &ngayTim)
{
    Node *p = list.first;
    bool found = false;
    cout << "Danh sach sinh vien co ngay sinh " << ngayTim.ngay << "/" << ngayTim.thang << "/" << ngayTim.nam << ":\n";
    while (p != nullptr)  // Lặp qua từng sinh viên để kiểm tra ngày sinh
    {
        if (p->data.ngaySinh.ngay == ngayTim.ngay && 
            p->data.ngaySinh.thang == ngayTim.thang && 
            p->data.ngaySinh.nam == ngayTim.nam)
        {
            cout << "Ma SV: " << p->data.maSV << endl;
            cout << "Ho ten: " << p->data.hoTen << endl;
            cout << "Gioi tinh: " << (p->data.gioiTinh ? "Nam" : "Nu") << endl;
            cout << "Dia chi: " << p->data.diaChi << endl;
            cout << "Lop: " << p->data.lop << endl;
            cout << "Khoa: " << p->data.khoa << endl;
            cout << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found)
    {
        cout << "Khong co sinh vien nao co ngay sinh nay trong danh sach." << endl;
    }
}

// Hàm xóa sinh viên có ngày sinh trùng với ngày tìm
void removeStudentsWithBirthday(List &list, const Ngay &ngayTim)
{
    Node *current = list.first;
    Node *previous = nullptr;

    while (current != nullptr)
    {
        if (current->data.ngaySinh.ngay == ngayTim.ngay && 
            current->data.ngaySinh.thang == ngayTim.thang && 
            current->data.ngaySinh.nam == ngayTim.nam)
        {
            if (previous == nullptr)  // Kiểm tra nếu là phần tử đầu tiên
            {
                list.first = current->next;
                if (list.first == nullptr)
                    list.last = nullptr;
                delete current;
                current = list.first;
            }
            else
            {
                previous->next = current->next;
                if (current->next == nullptr) // Kiểm tra nếu là phần tử cuối
                    list.last = previous;
                delete current;
                current = previous->next;
            }
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

int main()
{
    List listSV;
    initList(listSV);           // Khởi tạo danh sách sinh viên
    nhapListSV(listSV);         // Nhập danh sách sinh viên

    cout << "Danh sach sinh vien:" << endl;
    printList(listSV);          // In danh sách sinh viên

    Ngay ngayTim;
    cout << "Nhap ngay sinh can xoa (dd mm yyyy): ";
    cin >> ngayTim.ngay >> ngayTim.thang >> ngayTim.nam;   // Nhập ngày sinh cần xóa

    removeStudentsWithBirthday(listSV, ngayTim);           // Xóa sinh viên có ngày sinh giống ngày đã nhập

    cout << "Danh sach sinh vien sau khi xoa sinh vien co ngay sinh " << ngayTim.ngay << "/" << ngayTim.thang << "/" << ngayTim.nam << ":\n";
    printList(listSV);          // In lại danh sách sinh viên sau khi xóa

    return 0;
}
