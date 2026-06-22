#include <iostream>
#include <fstream>
#include <string>
#include "Phong.h"

using namespace std;
NodePhong* danhSachPhong = NULL;

void ghiFilePhong() {
    ofstream fileOut("Phong.txt");
    if (!fileOut.is_open()) {
        cout << "[LOI] Khong the mo file Phong.txt de ghi!\n";
        return;
    }
    NodePhong* p = danhSachPhong;
    while (p != NULL) {
        fileOut << p->data.maPhong << "\n"
                << p->data.loaiPhong << "\n"
                << (long long)p->data.donGia << "\n" 
                << p->data.soNguoiHienTai << "\n"
                << p->data.trangThai << "\n";
        p = p->next;
    }
    fileOut.close();
    cout << "=> Da luu danh sach phong xuong file Phong.txt!\n";
}

void docFilePhong() {
    ifstream fileIn("Phong.txt");
    if (!fileIn.is_open()) return; 

    string ma;
    while (getline(fileIn, ma)) {
        if (ma.empty()) continue;
        
        NodePhong* pMoi = new NodePhong;
        pMoi->data.maPhong = ma;

        string temp;
        getline(fileIn, temp); pMoi->data.loaiPhong = stoi(temp);
        getline(fileIn, temp); pMoi->data.donGia = stod(temp);
        getline(fileIn, temp); pMoi->data.soNguoiHienTai = stoi(temp);
        getline(fileIn, temp); pMoi->data.trangThai = stoi(temp);

        pMoi->next = NULL;

        if (danhSachPhong == NULL) {
            danhSachPhong = pMoi;
        } else {
            NodePhong* p = danhSachPhong;
            while (p->next != NULL) p = p->next;
            p->next = pMoi;
        }
    }
    fileIn.close();
    cout << "=> Da nap du lieu phong tu file!\n";
}

void themPhong() {
    NodePhong* pMoi = new NodePhong;
    cout << "\n--- NHAP THONG TIN PHONG MOI ---\n";
    cin.ignore();
    
    cout << "1. Nhap Ma phong (VD: B5-101): ";
    getline(cin, pMoi->data.maPhong);

    // Ép buộc người dùng chỉ được nhập 4, 6 hoặc 8
    int loai;
    do {
        cout << "2. Loai phong (Chi duoc nhap 4, 6 hoac 8): ";
        cin >> loai;
        if (loai != 4 && loai != 6 && loai != 8) {
            cout << "   [LOI] KTX chi co phong 4, 6 hoac 8 giuong. Vui long nhap lai!\n";
        }
    } while (loai != 4 && loai != 6 && loai != 8);
    
    pMoi->data.loaiPhong = loai;

    // Tự động gán đơn giá trên 1 KỲ HỌC
    if (loai == 4) {
        pMoi->data.donGia = 1500000; 
    } else if (loai == 6) {
        pMoi->data.donGia = 1000000; 
    } else if (loai == 8) {
        pMoi->data.donGia = 750000;  
    }

    cout << "=> He thong tu dong ap dung don gia: " << (long long)pMoi->data.donGia << " VND/ky hoc\n";

    pMoi->data.soNguoiHienTai = 0; 
    pMoi->data.trangThai = 1;      
    pMoi->next = NULL;

    if (danhSachPhong == NULL) {
        danhSachPhong = pMoi;
    } else {
        NodePhong* p = danhSachPhong;
        while (p->next != NULL) p = p->next;
        p->next = pMoi;
    }
    cout << "=> Them phong thanh cong!\n";
}

void inDanhSachPhong() {
    cout << "\n--- DANH SACH PHONG KTX ---\n";
    if (danhSachPhong == NULL) {
        cout << "He thong chua co du lieu phong!\n";
        return;
    }
    
    NodePhong* p = danhSachPhong;
    int stt = 1;
    while (p != NULL) {
        cout << "[" << stt++ << "] Ma phong: " << p->data.maPhong << " | Loai: " << p->data.loaiPhong << " giuong\n";
        cout << "    Don gia: " << (long long)p->data.donGia << " VND/ky hoc\n";
        cout << "    So nguoi hien tai: " << p->data.soNguoiHienTai << "/" << p->data.loaiPhong << "\n";
        cout << "    Trang thai: " << (p->data.trangThai == 1 ? "Con cho" : "HET CHO") << "\n";
        cout << "    ----------------------------------------\n";
        p = p->next;
    }
}

void menuPhong() {
    int chon;
    bool quayLai = false;

    static bool daDocFile = false;
    if (!daDocFile) {
        docFilePhong();
        daDocFile = true;
    }

    while (!quayLai) {
        cout << "\n============= QUAN LY PHONG KTX =============\n";
        cout << "1. Them phong moi\n";
        cout << "2. In danh sach phong\n";
        cout << "3. Luu du lieu xuong file text (.txt)\n";
        cout << "0. Quay lai menu chinh\n";
        cout << "---------------------------------------------\n";
        cout << "Chon chuc nang: ";
        cin >> chon;

        switch (chon) {
            case 1: themPhong(); break;
            case 2: inDanhSachPhong(); break;
            case 3: ghiFilePhong(); break;
            case 0: quayLai = true; break;
            default: cout << "Loi! Vui long chon lai.\n"; break;
        }
    }
}