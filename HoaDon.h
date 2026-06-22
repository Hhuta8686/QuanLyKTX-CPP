#ifndef HOADON_H
#define HOADON_H

#include <string>
using namespace std;

struct HoaDon {
    string maHD;        
    string maSV;        
    string maPhong;     
    string kyHoc;        
    double tienDien;    
    double tienNuoc;    
    double tienPhong;   
    double tongTien;    
    int trangThai;      
};

struct NodeHoaDon {
    HoaDon data;
    NodeHoaDon* next;
};

void menuHoaDon();
void docFileHoaDon();
void ghiFileHoaDon();
void taoHoaDon();
void inDanhSachHoaDon();
void thanhToanHoaDon();

#endif