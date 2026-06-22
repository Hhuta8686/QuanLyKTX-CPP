#include <iostream>
#include <string>
#include "SinhVien.h"
#include "Phong.h"
#include "DangKy.h"

using namespace std;

extern NodeSinhVien* danhSachSinhVien;
extern NodePhong* danhSachPhong;

extern void ghiFileSinhVien();
extern void ghiFilePhong();

int layGioiTinhCuaPhong(string maPhong) {
    NodeSinhVien* tempSV = danhSachSinhVien;
    while (tempSV != NULL) {
        if (tempSV->data.maPhong == maPhong) {
            return tempSV->data.gioiTinh; 
        }
        tempSV = tempSV->next;
    }
    return 0; 
}

void dangKyPhong() {
    string maSV, maPhong;
    cout << "\n--- DANG KY XEP PHONG KTX ---\n";
    cout << "Nhap Ma Sinh Vien: "; getline(cin, maSV);
    cout << "Nhap Ma Phong muon xep (VD: B5-101): "; getline(cin, maPhong);

    NodeSinhVien* pSV = danhSachSinhVien;
    while (pSV != NULL && pSV->data.maSV != maSV) {
        pSV = pSV->next;
    }

    if (pSV == NULL) {
        cout << "[LOI] Khong tim thay Sinh vien co ma: " << maSV << "\n";
        return;
    }

    if (pSV->data.maPhong != "Chua xep") {
        cout << "[LOI] Sinh vien nay da duoc xep phong: " << pSV->data.maPhong << ". Khong the dang ky moi!\n";
        return;
    }

    NodePhong* pPhong = danhSachPhong;
    while (pPhong != NULL && pPhong->data.maPhong != maPhong) {
        pPhong = pPhong->next;
    }

    if (pPhong == NULL) {
        cout << "[LOI] Khong tim thay Ma phong: " << maPhong << " trong he thong!\n";
        return;
    }

    if (pPhong->data.trangThai == 0) {
        cout << "[LOI] Phong " << maPhong << " hien tai da HET CHO!\n";
        return;
    }

    int gioiTinhPhong = layGioiTinhCuaPhong(maPhong);
    if (gioiTinhPhong != 0 && gioiTinhPhong != pSV->data.gioiTinh) {
        cout << "[LOI] Phong nay dang danh cho sinh vien khac gioi tinh!\n";
        return;
    }

    pSV->data.maPhong = maPhong;             
    pPhong->data.soNguoiHienTai++;           

    if (pPhong->data.soNguoiHienTai == pPhong->data.loaiPhong) {
        pPhong->data.trangThai = 0; 
    }

    cout << "=> Xep phong thanh cong! Sinh vien " << pSV->data.hoTen << " da vao phong " << maPhong << ".\n";
    
  
    ghiFileSinhVien();
    ghiFilePhong();
}

void chuyenPhong() {
    string maSV, maPhongMoi;
    cout << "\n--- CHUYEN PHONG KY TUC XA ---\n";
    cout << "Nhap Ma Sinh Vien can chuyen: "; getline(cin, maSV);
    cout << "Nhap Ma Phong MOI muon chuyen den: "; getline(cin, maPhongMoi);

    NodeSinhVien* pSV = danhSachSinhVien;
    while (pSV != NULL && pSV->data.maSV != maSV) {
        pSV = pSV->next;
    }

    if (pSV == NULL) {
        cout << "[LOI] Khong tim thay Sinh vien co ma: " << maSV << "\n";
        return;
    }

    string maPhongCu = pSV->data.maPhong;
    if (maPhongCu == "Chua xep") {
        cout << "[LOI] Sinh vien nay dang o trang thai 'Chua xep' phong. Vui long chon chuc nang Dang ky xep phong!\n";
        return;
    }

    if (maPhongCu == maPhongMoi) {
        cout << "[LOI] Phong moi trung voi phong hien tai sinh vien dang o!\n";
        return;
    }

    NodePhong* pPhongMoi = danhSachPhong;
    while (pPhongMoi != NULL && pPhongMoi->data.maPhong != maPhongMoi) {
        pPhongMoi = pPhongMoi->next;
    }

    if (pPhongMoi == NULL) {
        cout << "[LOI] Khong tim thay Ma phong moi: " << maPhongMoi << " trong KTX!\n";
        return;
    }

    if (pPhongMoi->data.trangThai == 0) {
        cout << "[LOI] Phong moi " << maPhongMoi << " hien tai da HET CHO!\n";
        return;
    }

    int gioiTinhPhongMoi = layGioiTinhCuaPhong(maPhongMoi);
    if (gioiTinhPhongMoi != 0 && gioiTinhPhongMoi != pSV->data.gioiTinh) {
        cout << "[LOI] Phong moi khong phu hop voi gioi tinh cua sinh vien!\n";
        return;
    }

    NodePhong* pPhongCu = danhSachPhong;
    while (pPhongCu != NULL) {
        if (pPhongCu->data.maPhong == maPhongCu) {
            pPhongCu->data.soNguoiHienTai--;
            pPhongCu->data.trangThai = 1; 
            break;
        }
        pPhongCu = pPhongCu->next;
    }

    pPhongMoi->data.soNguoiHienTai++;
    if (pPhongMoi->data.soNguoiHienTai == pPhongMoi->data.loaiPhong) {
        pPhongMoi->data.trangThai = 0;
    }
    
   
    pSV->data.maPhong = maPhongMoi;

    cout << "=> Chuyen phong thanh cong! Sinh vien " << pSV->data.hoTen 
         << " da chuyen tu phong " << maPhongCu << " sang phong " << maPhongMoi << ".\n";
         
    
    ghiFileSinhVien();
    ghiFilePhong();
}

void giaHanThuePhong() {
    string maSV, kyMoi;
    cout << "\n--- GIA HAN HOP DONG THUE PHONG ---\n";
    cout << "Nhap Ma Sinh Vien can gia han: "; getline(cin, maSV);

    NodeSinhVien* pSV = danhSachSinhVien;
    while (pSV != NULL && pSV->data.maSV != maSV) {
        pSV = pSV->next;
    }

    if (pSV == NULL) {
        cout << "[LOI] Khong tim thay Sinh vien co ma: " << maSV << "\n";
        return;
    }

    if (pSV->data.maPhong == "Chua xep") {
        cout << "[LOI] Sinh vien " << pSV->data.hoTen << " chua co phong o KTX. Vui long chon Dang ky xep phong!\n";
        return;
    }

    cout << "-> Sinh vien: " << pSV->data.hoTen << " dang o phong: " << pSV->data.maPhong << "\n";
    cout << "Nhap Hoc ky muon gia han tiep theo (VD: 20261): "; getline(cin, kyMoi);

    cout << "=> [THANH CONG] Da ghi nhan gia han hop dong thue phong KTX cho sinh vien