#include<iostream> 

using namespace std; 

// Định nghĩa cấu trúc Ngay
struct Ngay
{
    int ngay, thang, nam; // Các thành phần ngày, tháng, năm
};

// Định nghĩa cấu trúc SinhVien
struct SinhVien
{
    char maSV[8]; // Mã sinh viên
    char hoTen[50]; // Họ tên
    int gioiTinh; // Giới tính 
    Ngay ngaySinh; // Ngày sinh
    char diaChi[100]; // Địa chỉ
    char lop[12]; // Lớp
    char khoa[7]; // Khoa
};

// Định nghĩa cấu trúc Node
struct Node 
{
    SinhVien data; // Dữ liệu sinh viên
    Node *link; // Con trỏ liên kết đến node tiếp theo
};

// Định nghĩa cấu trúc List
struct List
{
    Node *first; // Con trỏ đến node đầu tiên
    Node *last; // Con trỏ đến node cuối cùng
};

// Hàm nhập vào danh sách sinh viên ListSV
void nhapDanhSachSinhVien(List &ListSV)
{
    int n; // Số lượng sinh viên
    cout << "Nhap so luong sinh vien: "; // Yêu cầu nhập số lượng sinh viên
    cin >> n; // Nhập số lượng sinh viên
    for (int i = 0; i < n; i++) // Vòng lặp nhập thông tin từng sinh viên
    {
        SinhVien sv; // Khai báo biến sinh viên
        cout << "Nhap thong tin sinh vien thu " << i + 1 << endl; // Yêu cầu nhập thông tin sinh viên thứ i+1
        cout << "Ma sinh vien: "; // Yêu cầu nhập mã sinh viên
        cin >> sv.maSV; // Nhập mã sinh viên
        cout << "Ho ten: "; // Yêu cầu nhập họ tên
        cin.ignore(); // Bỏ qua ký tự xuống dòng
        cin.getline(sv.hoTen, 50); // Nhập họ tên
        cout << "Gioi tinh (0: Nu, 1: Nam): "; // Yêu cầu nhập giới tính
        cin >> sv.gioiTinh; // Nhập giới tính
        cout << "Ngay sinh: "; // Yêu cầu nhập ngày sinh
        cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam; // Nhập ngày, tháng, năm sinh
        cout << "Dia chi: "; // Yêu cầu nhập địa chỉ
        cin.ignore(); // Bỏ qua ký tự xuống dòng
        cin.getline(sv.diaChi, 100); // Nhập địa chỉ
        cout << "Lop: "; // Yêu cầu nhập lớp
        cin >> sv.lop; // Nhập lớp
        cout << "Khoa: "; // Yêu cầu nhập khóa
        cin >> sv.khoa; // Nhập khóa
        Node *p = new Node; // Tạo node mới
        p->data = sv; // Gán dữ liệu sinh viên cho node
        p->link = NULL; // Gán con trỏ link của node bằng NULL
        if (ListSV.first == NULL) // Nếu danh sách rỗng
        {
            ListSV.first = p; // Gán node đầu tiên
            ListSV.last = p; // Gán node cuối cùng
        }
        else // Nếu danh sách không rỗng
        {
            ListSV.last->link = p; // Gán link của node cuối cùng đến node mới
            ListSV.last = p; // Cập nhật node cuối cùng
        }
    }
}

// Hàm so sánh hai chuỗi ký tự
int compareStrings(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) { // So sánh từng ký tự của hai chuỗi
        str1++; // Tăng con trỏ str1
        str2++; // Tăng con trỏ str2
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2; // Trả về kết quả so sánh
}

// Hàm sắp xếp tăng dần theo mã sinh viên
void sapXepTangDanTheoMaSinhVien(List &ListSV)
{
    Node *p = ListSV.first; // Con trỏ p trỏ đến node đầu tiên
    while (p != NULL) // Duyệt qua từng node
    {
        Node *q = p->link; // Con trỏ q trỏ đến node tiếp theo của p
        while (q != NULL) // Duyệt qua các node còn lại
        {
            if (compareStrings(p->data.maSV, q->data.maSV) > 0) // So sánh mã sinh viên của p và q
            {
                SinhVien temp = p->data; // Hoán đổi dữ liệu của p và q
                p->data = q->data;
                q->data = temp;
            }
            q = q->link; // Chuyển q đến node tiếp theo
        }
        p = p->link; // Chuyển p đến node tiếp theo
    }
}

// Hàm in ra danh sách sinh viên ListSV
void inDanhSachSinhVien(List ListSV)
{
    Node *p = ListSV.first; // Con trỏ p trỏ đến node đầu tiên
    while (p != NULL) // Duyệt qua từng node
    {
        cout << "Ma sinh vien: " << p->data.maSV << endl; // In mã sinh viên
        cout << "Ho ten: " << p->data.hoTen << endl; // In họ tên
        cout << "Gioi tinh: " << p->data.gioiTinh << endl; // In giới tính
        cout << "Ngay sinh: " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl; // In ngày sinh
        cout << "Dia chi: " << p->data.diaChi << endl; // In địa chỉ
        cout << "Lop: " << p->data.lop << endl; // In lớp
        cout << "Khoa: " << p->data.khoa << endl; // In khoa
        cout << "-----------------------------------" << endl; // In dòng phân cách
        p = p->link; // Chuyển p đến node tiếp theo
    }
}

// Hàm thêm một sinh viên mới vào danh sách ListSV đã sắp xếp và SV được sắp xếp theo đúng thứ tự ở DS mới
void themSinhVien(List &ListSV, SinhVien sv) {
    Node *p = new Node; // Tạo node mới
    p->data = sv; // Gán dữ liệu sinh viên cho node
    p->link = NULL; // Gán con trỏ link của node bằng NULL
    if (ListSV.first == NULL) { // Nếu danh sách rỗng
        ListSV.first = p; // Gán node đầu tiên
        ListSV.last = p; // Gán node cuối cùng
    } else { // Nếu danh sách không rỗng
        Node *q = ListSV.first; // Con trỏ q trỏ đến node đầu tiên
        Node *prev = NULL; // Con trỏ prev trỏ đến node trước q
        while (q != NULL && compareStrings(q->data.maSV, sv.maSV) < 0) { // Duyệt qua các node và tìm vị trí chèn
            prev = q; // Cập nhật prev
            q = q->link; // Chuyển q đến node tiếp theo
        }
        if (prev == NULL) { // Nếu chèn vào đầu danh sách
            p->link = ListSV.first; // Gán link của node mới đến node đầu tiên
            ListSV.first = p; // Cập nhật node đầu tiên
        } else { // Nếu chèn vào giữa hoặc cuối danh sách
            p->link = q; // Gán link của node mới đến node q
            prev->link = p; // Gán link của prev đến node mới
        }
    }
}

// Hàm in ra các sinh viên có cùng ngày sinh, nếu không tìm thấy sinh viên có cùng ngày sinh thì in thông báo “không tìm thấy sinh viên cùng ngày sinh”
void inSinhVienCungNgaySinh(List ListSV, Ngay ngaySinh) {
    Node *p = ListSV.first; // Con trỏ p trỏ đến node đầu tiên
    bool found = false; // Biến kiểm tra có tìm thấy sinh viên cùng ngày sinh hay không
    while (p != NULL) { // Duyệt qua từng node
        if (p->data.ngaySinh.ngay == ngaySinh.ngay && p->data.ngaySinh.thang == ngaySinh.thang && p->data.ngaySinh.nam == ngaySinh.nam) { // Kiểm tra ngày sinh
            cout << "Ma sinh vien: " << p->data.maSV << endl; // In mã sinh viên
            cout << "Ho ten: " << p->data.hoTen << endl; // In họ tên
            cout << "Gioi tinh: " << p->data.gioiTinh << endl; // In giới tính
            cout << "Ngay sinh: " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl; // In ngày sinh
            cout << "Dia chi: " << p->data.diaChi << endl; // In địa chỉ
            cout << "Lop: " << p->data.lop << endl; // In lớp
            cout << "Khoa: " << p->data.khoa << endl; // In khóa
            found = true; // Cập nhật biến kiểm tra
        }
        p = p->link; // Chuyển p đến node tiếp theo
    }
    if (!found) { // Nếu không tìm thấy sinh viên cùng ngày sinh
        cout << "Khong tim thay sinh vien cung ngay sinh" << endl; // In thông báo
    }
}

// Hàm loại bỏ các sinh viên có cùng ngày sinh ra khỏi danh sách ListSV
void loaiBoSinhVienCungNgaySinh(List &ListSV, Ngay ngaySinh) {
    Node *p = ListSV.first; // Con trỏ p trỏ đến node đầu tiên
    Node *prev = NULL; // Con trỏ prev trỏ đến node trước p
    while (p != NULL) { // Duyệt qua từng node
        if (p->data.ngaySinh.ngay == ngaySinh.ngay && p->data.ngaySinh.thang == ngaySinh.thang && p->data.ngaySinh.nam == ngaySinh.nam) { // Kiểm tra ngày sinh
            if (prev == NULL) { // Nếu node cần xóa là node đầu tiên
                ListSV.first = p->link; // Cập nhật node đầu tiên
            } else { // Nếu node cần xóa không phải là node đầu tiên
                prev->link = p->link; // Gán link của prev đến node sau p
            }
            delete p; // Giải phóng bộ nhớ của node p
            p = prev == NULL ? ListSV.first : prev->link; // Cập nhật p
        } else { // Nếu không trùng ngày sinh
            prev = p; // Cập nhật prev
            p = p->link; // Chuyển p đến node tiếp theo
        }
    }
}

// Hàm main
int main() {
    List ListSV; // Khai báo danh sách sinh viên
    ListSV.first = NULL; // Khởi tạo danh sách rỗng
    ListSV.last = NULL; // Khởi tạo danh sách rỗng
    
    // Nhập danh sách sinh viên ban đầu
    nhapDanhSachSinhVien(ListSV);
    cout << "\nDanh sach sinh vien truoc khi sap xep: " << endl; // In danh sách sinh viên trước khi sắp xếp
    inDanhSachSinhVien(ListSV);
    
    // Sắp xếp danh sách sinh viên theo mã sinh viên
    sapXepTangDanTheoMaSinhVien(ListSV);
    cout << "\nDanh sach sinh vien sau khi sap xep: " << endl; // In danh sách sinh viên sau khi sắp xếp
    inDanhSachSinhVien(ListSV);
    
    // Thêm sinh viên mới vào danh sách đã sắp xếp
    SinhVien sv; // Khai báo biến sinh viên
    cout << "\nNhap thong tin sinh vien can them:\n"; // Yêu cầu nhập thông tin sinh viên cần thêm
    cout << "Ma sinh vien: "; // Yêu cầu nhập mã sinh viên
    cin >> sv.maSV; // Nhập mã sinh viên
    cout << "Ho ten: "; // Yêu cầu nhập họ tên
    cin.ignore(); // Bỏ qua ký tự xuống dòng
    cin.getline(sv.hoTen, 50); // Nhập họ tên
    cout << "Gioi tinh (0: Nu, 1: Nam): "; // Yêu cầu nhập giới tính
    cin >> sv.gioiTinh; // Nhập giới tính
    cout << "Ngay sinh (ngay thang nam): "; // Yêu cầu nhập ngày sinh
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam; // Nhập ngày, tháng, năm sinh
    cout << "Dia chi: "; // Yêu cầu nhập địa chỉ
    cin.ignore(); // Bỏ qua ký tự xuống dòng
    cin.getline(sv.diaChi, 100); // Nhập địa chỉ
    cout << "Lop: "; // Yêu cầu nhập lớp
    cin >> sv.lop; // Nhập lớp
    cout << "Khoa: "; // Yêu cầu nhập khoa
    cin >> sv.khoa; // Nhập khoa
    
    themSinhVien(ListSV, sv); // Thêm sinh viên vào danh sách
    cout << "\nDanh sach sinh vien sau khi them sinh vien moi:\n"; // In danh sách sinh viên sau khi thêm sinh viên mới
    sapXepTangDanTheoMaSinhVien(ListSV); // Sắp xếp lại danh sách sinh viên
    inDanhSachSinhVien(ListSV); // In danh sách sinh viên
    
    // Tìm sinh viên có cùng ngày sinh
    Ngay ngaySinh; // Khai báo biến ngày sinh
    cout << "\nNhap ngay sinh de tim sinh vien co cung ngay sinh (ngay thang nam): "; // Yêu cầu nhập ngày sinh để tìm sinh viên có cùng ngày sinh
    cin >> ngaySinh.ngay >> ngaySinh.thang >> ngaySinh.nam; // Nhập ngày, tháng, năm sinh
    cout << "\nDanh sach sinh vien co cung ngay sinh:\n"; // In danh sách sinh viên có cùng ngày sinh
    inSinhVienCungNgaySinh(ListSV, ngaySinh); // Tìm và in sinh viên có cùng ngày sinh
    
    // Xóa sinh viên có cùng ngày sinh
    cout << "\nXoa sinh vien co cung ngay sinh da nhap.\n"; // Thông báo xóa sinh viên có cùng ngày sinh đã nhập
    loaiBoSinhVienCungNgaySinh(ListSV, ngaySinh); // Xóa sinh viên có cùng ngày sinh
    cout << "\nDanh sach sinh vien sau khi xoa:\n"; // In danh sách sinh viên sau khi xóa
    inDanhSachSinhVien(ListSV); // In danh sách sinh viên
    
    return 0; // Kết thúc chương trình
}