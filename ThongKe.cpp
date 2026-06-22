#include <iostream>
#include <string>
#include "SinhVien.h"
#include "Phong.h"
#include "HoaDon.h"
#include "ThongKe.h"

using namespace std;

extern NodeSinhVien* danhSachSinhVien;
extern NodePhong* danhSachPhong;
extern NodeHoaDon* danhSachHoaDon;

void thongKePhongKTX() {
    cout << "\n==================================================";
    cout << "\n      THONG KE CHI TIET TRANG THAI PHONG KTX     ";
    cout << "\n==================================================\n";

    if (danhSachPhong == NULL) {
        cout << "=> He thong chua co du lieu phong!\n";
        return;
    }

    NodePhong* p = danhSachPhong;
    string dsPhongTrong = "";
    string dsPhongDay = "";
    int stt = 1;

    while (p != NULL) {
        double tiLeLapDay = ((double)p->data.soNguoiHienTai / p->data.loaiPhong) * 100;

        cout << "[" << stt++ << "] Phong: " << p->data.maPhong 
             << " | Suc chua: " << p->data.soNguoiHienTai << "/" << p->data.loaiPhong << " SV"
             << " | Ti le lap day: " << tiLeLapDay << "%\n";

        if (p->data.soNguoiHienTai == 0) {
            dsPhongTrong += p->data.maPhong + "   ";
        } else if (p->data.soNguoiHienTai == p->data.loaiPhong) {
            dsPhongDay += p->data.maPhong + "   ";
        }
        p = p->next;
    }

    cout << "--------------------------------------------------\n";
    cout << "=> DANH SACH PHONG CON TRONG TOAN BO: \n   " << (dsPhongTrong == "" ? "(Khong co)" : dsPhongTrong) << "\n\n";
    cout << "=> DANH SACH PHONG DA LAP DAY (FULL): \n   " << (dsPhongDay == "" ? "(Khong co)" : dsPhongDay) << "\n";
    cout << "==================================================\n";
}

void thongKeSinhVienKyLuat() {
    cout << "\n==================================================";
    cout << "\n         THONG KE VI PHAM KY LUAT SINH VIEN      ";
    cout << "\n==================================================\n";

    if (danhSachSinhVien == NULL) {
        cout << "=> He thong chua co du lieu sinh vien!\n";
        return;
    }

    NodeSinhVien* p = danhSachSinhVien;
    int stt = 1;
    bool coViPham = false;

    while (p != NULL) {
        if (p->data.soLanViPham > 0) {
            cout << "[" << stt++ << "] SV: " << p->data.hoTen 
                 << " | MSSV: " << p->data.maSV 
                 << " | Phong: " << p->data.maPhong 
                 << " -> Vi pham: " << p->data.soLanViPham << " loi.\n";
            coViPham = true;
        }
        p = p->next;
    }

    if (!coViPham) {
        cout << "=> Tuyet voi! Khong co sinh vien nao vi pham ky luat KTX.\n";
    }
    cout << "==================================================\n";
}

void thongKeSinhVienChuaDongTien() {
    cout << "\n==================================================";
    cout << "\n     DANH SACH SINH VIEN CHUA THANH TOAN HOA DON  ";
    cout << "\n==================================================\n";

    if (danhSachHoaDon == NULL) {
        cout << "=> He thong chua co du lieu hoa don!\n";
        return;
    }

    NodeHoaDon* pHD = danhSachHoaDon;
    bool coNguoiNo = false;
    int stt = 1;

    while (pHD != NULL) {
        if (pHD->data.trangThai == 0) {
            string tenSV = ""; 
            NodeSinhVien* pSV = danhSachSinhVien;
            
            while (pSV != NULL) {
                if (pSV->data.maSV == pHD->data.maSV) {
                    tenSV = pSV->data.hoTen;
                    break;
                }
                pSV = pSV->next;
            }
            
            if (tenSV.empty()) {
                pHD = pHD->next;
                continue;
            }
            
            cout << "[" << stt++ << "] SV: " << tenSV 
                 << " | MSSV: " << pHD->data.maSV 
                 << " | Phong: " << pHD->data.maPhong 
                 << " | Ky hoc: " << pHD->data.kyHoc << "\n";
            cout << "    >> Con no: " << (long long)pHD->data.tongTien << " VND "
                 << " (Dien: " << (long long)pHD->data.tienDien 
                 << " | Nuoc: " << (long long)pHD->data.tienNuoc 
                 << " | Phong: " << (long long)pHD->data.tienPhong << ")\n";
            cout << "    >> [Ma HD can thu: " << pHD->data.maHD << "]\n";
            cout << "  ------------------------------------------------\n";
            coNguoiNo = true;
        }
        pHD = pHD->next;
    }

    if (!coNguoiNo) {
        cout << "=> Tuyet voi! 100% sinh vien da hoan thanh nghia vu dong tien.\n";
    }
    cout << "==================================================\n";
}

void menuThongKe() {
    int chon;
    bool quayLai = false;

    if (danhSachSinhVien == NULL) { docFileSinhVien(); }
    if (danhSachHoaDon == NULL) { docFileHoaDon(); }

    while (!quayLai) {
        cout << "\n============= BAO CAO THONG KE SO LIEU =============\n";
        cout << "1. Thong ke trang thai va ti le lap day cac Phong\n";
        cout << "2. Thong ke danh sach Sinh Vien vi pham ky luat\n";
        cout << "3. Thong ke danh sach Sinh Vien CHUA DONG TIEN\n";
        cout << "0. Quay lai menu chinh\n";
        cout << "----------------------------------------------------\n";
        cout << "Chon chuc nang: ";
        cin >> chon;

        switch (chon) {
            case 1: thongKePhongKTX(); break;
            case 2: thongKeSinhVienKyLuat(); break;
            case 3: thongKeSinhVienChuaDongTien(); break;
            case 0: quayLai = true; break;
            default: cout << "Loi! Vui long chon lai.\n"; break;
        }
    }
}