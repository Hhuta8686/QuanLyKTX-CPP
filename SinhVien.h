#ifndef SINHVIEN_H
#define SINHVIEN_H

#include <string>
using namespace std;

struct SinhVien {
    string maSV;
    string hoTen;
    string lop;
    string queQuan;
    int gioiTinh;    // 1: Nam, 2: Nu
    int dienUuTien;  // 1->4
    string sdt;
    string maPhong;  // "Chua xep" hoac Ma phong cu the
    int soLanViPham;
};

struct NodeSinhVien {
    SinhVien data;
    NodeSinhVien* next;
};

extern NodeSinhVien* danhSachSinhVien;

void docFileSinhVien();
void ghiFileSinhVien();
void themSinhVien();
void inDanhSachSinhVien();
void timKiemSinhVien();
void suaThongTinSinhVien();
void ghiNhanViPham();
void xoaSinhVienViPham();
void menuSinhVien();
string dienUuTien(int loai);
string layGioiTinh(int gt);

#endif