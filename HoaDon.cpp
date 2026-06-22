#include <iostream>
#include <fstream>
#include <string>
#include "SinhVien.h" 
#include "Phong.h"
#include "HoaDon.h"

using namespace std;

NodeHoaDon* danhSachHoaDon = NULL;

extern NodePhong* danhSachPhong;
extern NodeSinhVien* danhSachSinhVien;

void ghiFileHoaDon() {
    ofstream fileOut("HoaDon.txt");
    if (!fileOut.is_open()) return;
    
    NodeHoaDon* p = danhSachHoaDon;
    while (p != NULL) {
        fileOut << p->data.maHD << "\n" << p->data.maSV << "\n" << p->data.maPhong << "\n" 
                << p->data.kyHoc << "\n" << (long long)p->data.tienDien << "\n" 
                << (long long)p->data.tienNuoc << "\n" << (long long)p->data.tienPhong << "\n" 
                << (long long)p->data.tongTien << "\n" << p->data.trangThai << "\n";
        p = p->next;
    }
    fileOut.close();
    cout << "=> Da luu danh sach hoa don ca nhan xuong file!\n";
}

void docFileHoaDon() {
    ifstream fileIn("HoaDon.txt");
    if (!fileIn.is_open()) return;

    string ma;
    while (getline(fileIn, ma)) {
        if (ma.empty()) continue;
        NodeHoaDon* pMoi = new NodeHoaDon;
        pMoi->data.maHD = ma;
        getline(fileIn, pMoi->data.maSV);
        getline(fileIn, pMoi->data.maPhong);
        getline(fileIn, pMoi->data.kyHoc);

        string temp;
        getline(fileIn, temp); pMoi->data.tienDien = stod(temp);
        getline(fileIn, temp); pMoi->data.tienNuoc = stod(temp);
        getline(fileIn, temp); pMoi->data.tienPhong = stod(temp);
        getline(fileIn, temp); pMoi->data.tongTien = stod(temp);
        getline(fileIn, temp); pMoi->data.trangThai = stoi(temp);

        pMoi->next = NULL;
        if (danhSachHoaDon == NULL) {
            danhSachHoaDon = pMoi;
        } else {
            NodeHoaDon* p = danhSachHoaDon;
            while (p->next != NULL) p = p->next;
            p->next = pMoi;
        }
    }
    fileIn.close();
}

void taoHoaDon() {
    string maPhong, kyHoc, maHDGoc;
    cout << "\n--- TINH TIEN DIEN - NUOC - PHONG THEO DOT ---\n";
    cin.ignore();
    cout << "1. Nhap Ma Hoa Don goc (VD: HD01): "; getline(cin, maHDGoc);
    cout << "2. Nhap Ma Phong can tinh tien: "; getline(cin, maPhong);
    cout << "3. Nhap Ky hoc (VD: 20251): "; getline(cin, kyHoc);

    NodePhong* pPhong = danhSachPhong;
    while (pPhong != NULL && pPhong->data.maPhong != maPhong) {
        pPhong = pPhong->next;
    }

    if (pPhong == NULL) {
        cout << "[LOI] Khong tim thay ma phong nay tren he thong!\n";
        return;
    }

    if (pPhong->data.soNguoiHienTai == 0) {
        cout << "[LOI] Phong nay hien dang trong (0 sinh vien), khong the tao hoa don!\n";
        return;
    }

    int dienCu, dienMoi, nuocCu, nuocMoi;
    do {
        cout << "4. Nhap Chi so Dien CU - MOI: "; cin >> dienCu >> dienMoi;
    } while (dienMoi < dienCu);

    do {
        cout << "5. Nhap Chi so Nuoc CU - MOI: "; cin >> nuocCu >> nuocMoi;
    } while (nuocMoi < nuocCu);

    int soNguoi = pPhong->data.soNguoiHienTai;
    double tienDienMoiNguoi = ((dienMoi - dienCu) * 3000) / soNguoi;
    double tienNuocMoiNguoi = ((nuocMoi - nuocCu) * 10000) / soNguoi;

    NodeSinhVien* pSV = danhSachSinhVien;
    int demHoaDon = 0;

    while (pSV != NULL) {
        if (pSV->data.maPhong == maPhong) {
            NodeHoaDon* pMoi = new NodeHoaDon;
            
            pMoi->data.maHD = maHDGoc + "_" + pSV->data.maSV;
            pMoi->data.maSV = pSV->data.maSV;
            pMoi->data.maPhong = maPhong;
            pMoi->data.kyHoc = kyHoc;
            pMoi->data.tienDien = tienDienMoiNguoi;
            pMoi->data.tienNuoc = tienNuocMoiNguoi;
            pMoi->data.tienPhong = pPhong->data.donGia;
            pMoi->data.tongTien = tienDienMoiNguoi + tienNuocMoiNguoi + pPhong->data.donGia;
            pMoi->data.trangThai = 0;
            pMoi->next = NULL;

            if (danhSachHoaDon == NULL) danhSachHoaDon = pMoi;
            else {
                NodeHoaDon* tmp = danhSachHoaDon;
                while (tmp->next != NULL) tmp = tmp->next;
                tmp->next = pMoi;
            }
            demHoaDon++;
        }
        pSV = pSV->next;
    }

    cout << "=> [THANH CONG] He thong da tu dong chia deu va phat sinh " << demHoaDon 
         << " hoa don ca nhan cho cac thanh vien phong " << maPhong << ".\n";
    ghiFileHoaDon();
}

void inDanhSachHoaDon() {
    cout << "\n--- DANH SACH HOA DON CHI TIET CUA TUNG SINH VIEN ---\n";
    if (danhSachHoaDon == NULL) {
        cout << "Chua co hoa don nao!\n"; return;
    }
    NodeHoaDon* p = danhSachHoaDon;
    while (p != NULL) {
        string tenSV = ""; 
        NodeSinhVien* pSV = danhSachSinhVien;
        
        while (pSV != NULL) {
            if (pSV->data.maSV == p->data.maSV) { 
                tenSV = pSV->data.hoTen; 
                break; 
            }
            pSV = pSV->next;
        }

        if (tenSV.empty()) {
            p = p->next;
            continue; 
        }

        cout << "Ma HD: " << p->data.maHD << " | SV: " << tenSV << " (" << p->data.maSV << ")\n";
        cout << "    Phong: " << p->data.maPhong << " | Hoc ky: " << p->data.kyHoc << "\n";
        cout << "    - Tien dien (da chia):  " << (long long)p->data.tienDien << " VND\n";
        cout << "    - Tien nuoc (da chia):  " << (long long)p->data.tienNuoc << " VND\n";
        cout << "    - Tien phong/ky:         " << (long long)p->data.tienPhong << " VND\n";
        cout << "    >> TONG PHAI DONG:       " << (long long)p->data.tongTien << " VND\n";
        cout << "    >> Trang thai:           " << (p->data.trangThai == 1 ? "DA THANH TOAN" : "CHUA THANH TOAN") << "\n";
        cout << "    --------------------------------------------------\n";
        p = p->next;
    }
}

void thanhToanHoaDon() {
    string maHD;
    cout << "\n--- THU TIEN HOA DON CA NHAN ---\n";
    cin.ignore();
    cout << "Nhap chinh xac Ma Hoa Don ca nhan de gach no (VD: HD01_MSSV): "; getline(cin, maHD);

    NodeHoaDon* p = danhSachHoaDon;
    while (p != NULL) {
        if (p->data.maHD == maHD) {
            if (p->data.trangThai == 1) {
                cout << "=> Sinh vien nay da dong tien tu truoc!\n"; return;
            }
            p->data.trangThai = 1; 
            cout << "=> Da ghi nhan dong tien thanh cong cho Hoa don: " << maHD << "\n";
            ghiFileHoaDon();
            return;
        }
        p = p->next;
    }
    cout << "[LOI] Khong tim thay ma hoa don ca nhan nay!\n";
}

void menuHoaDon() {
    int chon; bool quayLai = false;
    
    if (danhSachSinhVien == NULL) { docFileSinhVien(); }
    
    static bool daDocFile = false;
    if (!daDocFile) { docFileHoaDon(); daDocFile = true; }

    while (!quayLai) {
        cout << "\n============= QUAN LY HOA DON KTX =============\n";
        cout << "1. Nhap so dien nuoc phong (Tu dong phat hoa don le)\n";
        cout << "2. In danh sach hoa don ca nhan\n";
        cout << "3. Ghi nhan thanh toan (Thu tien tung nguoi)\n";
        cout << "4. Luu danh sach hoa don xuong file (.txt)\n";
        cout << "0. Quay lai menu chinh\n";
        cout << "---------------------------------------------\n";
        cout << "Chon chuc nang: "; cin >> chon;
        switch (chon) {
            case 1: taoHoaDon(); break;
            case 2: inDanhSachHoaDon(); break;
            case 3: thanhToanHoaDon(); break;
            case 4: ghiFileHoaDon(); break;
            case 0: quayLai = true; break;
            default: cout << "Loi! Vui long chon lai.\n"; break;
        }
    }
}