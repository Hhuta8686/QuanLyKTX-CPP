#ifndef PHONG_H
#define PHONG_H

#include <string>
using namespace std;

struct Phong {
    string maPhong;
    int loaiPhong;       // Chỉ nhận giá trị: 4, 6, hoặc 8 giường
    double donGia;       // Giá thuê 1 kỳ học
    int soNguoiHienTai;  // Mặc định bằng 0 khi mới tạo
    int trangThai;       // 1: Còn chỗ, 0: Hết chỗ
};

struct NodePhong {
    Phong data;
    NodePhong* next;
};


void menuPhong();
void docFilePhong();
void ghiFilePhong();
void themPhong();
void inDanhSachPhong();

#endif