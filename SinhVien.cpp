#include <iostream>
#include <fstream> 
#include <string>
#include "SinhVien.h"

using namespace std;

NodeSinhVien* danhSachSinhVien = NULL;

string dienUuTien(int loai) {
    switch (loai) {
        case 1: return "Con TB/LS, Nguoi dan toc thieu so";
        case 2: return "Vung sau vung xa, Hai dao";
        case 3: return "Ho ngho, Can ngheo";
        case 4: return "Binh thuong (Khong uu tien)";
        default: return "Khong xac dinh";
    }
}

string layGioiTinh(int gt) {
    if (gt == 1) return "Nam";
    if (gt == 2) return "Nu";
    return "Khong xac dinh";
}

void ghiFileSinhVien() {
    ofstream fileOut("SinhVien.txt");
    if (!fileOut.is_open()) {
        cout << "[LOI] Khong the mo file SinhVien.txt de ghi!\n";
        return;
    }
    NodeSinhVien* p = danhSachSinhVien;
    while (p != NULL) {
        fileOut << p->data.maSV << "\n" 
                << p->data.hoTen << "\n" 
                << p->data.lop << "\n" 
                << p->data.queQuan << "\n" 
                << p->data.gioiTinh << "\n" 
                << p->data.dienUuTien << "\n" 
                << p->data.sdt << "\n"       
                << p->data.maPhong << "\n" 
                << p->data.soLanViPham << "\n";
        p = p->next;
    }
    fileOut.close();
    cout << "=> Da luu danh sach sinh vien xuong file SinhVien.txt!\n";
}

void docFileSinhVien() {
    ifstream fileIn("SinhVien.txt");
    if (!fileIn.is_open()) return; 

    string ma;
    while (getline(fileIn, ma)) {
        if (ma.empty()) continue; 
        NodeSinhVien* pMoi = new NodeSinhVien;
        pMoi->data.maSV = ma;
        getline(fileIn, pMoi->data.hoTen);
        getline(fileIn, pMoi->data.lop);
        getline(fileIn, pMoi->data.queQuan);
        
        string temp;
        getline(fileIn, temp); pMoi->data.gioiTinh = stoi(temp);
        getline(fileIn, temp); pMoi->data.dienUuTien = stoi(temp);
        getline(fileIn, pMoi->data.sdt);
        getline(fileIn, pMoi->data.maPhong);
        getline(fileIn, temp); pMoi->data.soLanViPham = stoi(temp);
        
        pMoi->next = NULL;
        if (danhSachSinhVien == NULL) {
            danhSachSinhVien = pMoi;
        } else {
            NodeSinhVien* p = danhSachSinhVien;
            while (p->next != NULL) p = p->next;
            p->next = pMoi;
        }
    }
    fileIn.close();
}

void themSinhVien() {
    NodeSinhVien* pMoi = new NodeSinhVien;
    cout << "\n--- NHAP THONG TIN HO SO ---";
    cin.ignore(); 
    
    // Kiem tra Ma SV (Khong de trong + Khong trung lap)
    while (true) {
        cout << "\n1. Nhap Ma SV: "; getline(cin, pMoi->data.maSV);
        if (pMoi->data.maSV.empty()) {
            cout << "   [LOI] Ma sinh vien khong duoc bo trong!\n";
            continue;
        }
        // Kiem tra trung ma
        bool trungMa = false;
        NodeSinhVien* pCheck = danhSachSinhVien;
        while (pCheck != NULL) {
            if (pCheck->data.maSV == pMoi->data.maSV) {
                trungMa = true;
                break;
            }
            pCheck = pCheck->next;
        }
        if (trungMa) {
            cout << "   [LOI] Ma sinh vien nay da ton tai trong he thong!\n";
        } else {
            break;
        }
    }

    // Kiem tra Ho Ten khong de trong
    do {
        cout << "2. Nhap Ho Ten: "; getline(cin, pMoi->data.hoTen);
        if (pMoi->data.hoTen.empty()) cout << "   [LOI] Ho ten khong duoc bo trong!\n";
    } while (pMoi->data.hoTen.empty());

    // Kiem tra Lop khong de trong
    do {
        cout << "3. Nhap Lop: "; getline(cin, pMoi->data.lop);
        if (pMoi->data.lop.empty()) cout << "   [LOI] Lop khong duoc bo trong!\n";
    } while (pMoi->data.lop.empty());

    // Kiem tra Que quan khong de trong
    do {
        cout << "4. Nhap Que quan: "; getline(cin, pMoi->data.queQuan);
        if (pMoi->data.queQuan.empty()) cout << "   [LOI] Que quan khong duoc bo trong!\n";
    } while (pMoi->data.queQuan.empty());
    
    int gt;
    do {
        cout << "5. Nhap Gioi tinh (1: Nam | 2: Nu): ";
        cin >> gt;
        if (gt != 1 && gt != 2) cout << "   [LOI] Gioi tinh khong hop le! Vui long nhap lai.\n";
    } while (gt != 1 && gt != 2);
    pMoi->data.gioiTinh = gt;

    // Kiem tra SDT khong de trong
    cin.ignore();
    do {
        cout << "6. Nhap So dien thoai ca nhan: "; getline(cin, pMoi->data.sdt);
        if (pMoi->data.sdt.empty()) cout << "   [LOI] So dien thoai khong duoc bo trong!\n";
    } while (pMoi->data.sdt.empty());

    // Kiem tra Dien uu tien (1->4)
    do {
        cout << "7. Nhap Dien uu tien (1->4): "; cin >> pMoi->data.dienUuTien;
        if (pMoi->data.dienUuTien < 1 || pMoi->data.dienUuTien > 4) {
            cout << "   [LOI] Dien uu tien phai nam trong khoang tu 1 den 4!\n";
        }
    } while (pMoi->data.dienUuTien < 1 || pMoi->data.dienUuTien > 4);
    
    pMoi->data.maPhong = "Chua xep"; 
    pMoi->data.soLanViPham = 0; 
    pMoi->next = NULL;

    if (danhSachSinhVien == NULL) danhSachSinhVien = pMoi; 
    else {
        NodeSinhVien* p = danhSachSinhVien;
        while (p->next != NULL) p = p->next;
        p->next = pMoi;
    }
    cout << "=> Them ho so sinh vien thanh cong!\n";
    ghiFileSinhVien(); 
}

void inDanhSachSinhVien() {
    cout << "\n--- DANH SACH HO SO SINH VIEN ---\n";
    if (danhSachSinhVien == NULL) {
        cout << "He thong chua co du lieu!\n"; return; 
    }
    NodeSinhVien* p = danhSachSinhVien;
    int stt = 1;
    while (p != NULL) {
        cout << "\n[" << stt++ << "] Ma SV: " << p->data.maSV << " | Ho ten: " << p->data.hoTen << "\n";
        cout << "    Gioi tinh: " << layGioiTinh(p->data.gioiTinh) << " | Lop: " << p->data.lop << "\n";
        cout << "    Uu tien: " << dienUuTien(p->data.dienUuTien) << " | Que quan: " << p->data.queQuan << "\n";
        cout << "    Lien he: " << p->data.sdt << "\n";
        cout << "    Phong: " << p->data.maPhong << " | So loi: " << p->data.soLanViPham << "\n";
        cout << "    --------------------------------------------------";
        p = p->next; 
    }
    cout << "\n";
}

void timKiemSinhVien() {
    string maCanTim;
    cout << "\n--- TIM KIEM SINH VIEN ---\n";
    cout << "Nhap Ma SV can tim: ";
    cin.ignore();
    getline(cin, maCanTim);

    NodeSinhVien* p = danhSachSinhVien;
    while (p != NULL) {
        if (p->data.maSV == maCanTim) {
            cout << "\n=> TIM THAY THONG TIN:\n";
            cout << "- Ho ten: " << p->data.hoTen << " | Gioi tinh: " << layGioiTinh(p->data.gioiTinh) << "\n";
            cout << "- Lop: " << p->data.lop << " | Que quan: " << p->data.queQuan << "\n";
            cout << "- Dien uu tien: " << dienUuTien(p->data.dienUuTien) << "\n";
            cout << "- Phong dang o: " << p->data.maPhong << "\n";
            cout << "- SDT ca nhan: " << p->data.sdt << "\n";
            cout << "- So loi vi pham: " << p->data.soLanViPham << "\n";
            return; 
        }
        p = p->next;
    }
    cout << "=> Khong tim thay sinh vien nao co ma: " << maCanTim << "\n";
}

void suaThongTinSinhVien() {
    string maCanSua;
    cout << "\n--- SUA THONG TIN SINH VIEN ---\n";
    cout << "Nhap Ma SV can sua: ";
    cin.ignore();
    getline(cin, maCanSua);

    NodeSinhVien* p = danhSachSinhVien;
    while (p != NULL) {
        if (p->data.maSV == maCanSua) {
            cout << "\n=> Da tim thay ho so cua: " << p->data.hoTen << "\n";
            cout << "1. Sua Ho ten\n";
            cout << "2. Sua Lop\n";
            cout << "3. Sua Que quan\n";
            cout << "4. Sua Gioi tinh\n";
            cout << "5. Sua SDT ca nhan\n";
            cout << "6. Sua Dien uu tien\n";
            cout << "Chon thong tin can sua (1-6): ";
            
            int chon;
            cin >> chon;
            cin.ignore(); 

            switch(chon) {
                case 1: 
                    do {
                        cout << "Nhap Ho ten moi: "; getline(cin, p->data.hoTen);
                    } while (p->data.hoTen.empty());
                    break;
                case 2: 
                    do {
                        cout << "Nhap Lop moi: "; getline(cin, p->data.lop);
                    } while (p->data.lop.empty());
                    break;
                case 3: 
                    do {
                        cout << "Nhap Que quan moi: "; getline(cin, p->data.queQuan);
                    } while (p->data.queQuan.empty());
                    break;
                case 4: 
                    int gt;
                    do {
                        cout << "Nhap Gioi tinh moi (1: Nam | 2: Nu): "; cin >> gt;
                    } while (gt != 1 && gt != 2);
                    p->data.gioiTinh = gt; break;
                case 5: 
                    do {
                        cout << "Nhap SDT moi: "; getline(cin, p->data.sdt);
                    } while (p->data.sdt.empty());
                    break;
                case 6: 
                    do {
                        cout << "Nhap Dien uu tien moi (1->4): "; cin >> p->data.dienUuTien;
                    } while (p->data.dienUuTien < 1 || p->data.dienUuTien > 4);
                    break;
                default: cout << "Lua chon khong hop le!\n"; return;
            }
            cout << "=> Cap nhat thong tin thanh cong!\n";
            ghiFileSinhVien();
            return; 
        }
        p = p->next;
    }
    cout << "=> Khong tim thay sinh vien nao co ma: " << maCanSua << "\n";
}

void ghiNhanViPham() {
    string ma;
    cout << "\nNhap Ma SV can ghi nhan vi pham: "; cin.ignore(); getline(cin, ma);
    
    NodeSinhVien* p = danhSachSinhVien;
    while (p != NULL) {
        if (p->data.maSV == ma) {
            p->data.soLanViPham++;
            cout << "=> Da ghi nhan! SV " << p->data.hoTen << " dang co " << p->data.soLanViPham << " loi.\n";
            ghiFileSinhVien();
            return;
        }
        p = p->next;
    }
    cout << "=> Khong tim thay sinh vien!\n";
}

void xoaSinhVienViPham() {
    int MAX_LOI = 3, soNguoiBiXoa = 0;
    while (danhSachSinhVien != NULL && danhSachSinhVien->data.soLanViPham >= MAX_LOI) {
        NodeSinhVien* toaCanXoa = danhSachSinhVien;    
        danhSachSinhVien = danhSachSinhVien->next;     
        cout << "- Da xoa SV: " << toaCanXoa->data.hoTen << "\n";
        delete toaCanXoa; soNguoiBiXoa++;
    }
    if (danhSachSinhVien != NULL) {
        NodeSinhVien* p = danhSachSinhVien;
        while (p->next != NULL) {
            if (p->next->data.soLanViPham >= MAX_LOI) {
                NodeSinhVien* toaCanXoa = p->next;     
                p->next = toaCanXoa->next;             
                cout << "- Da xoa SV: " << toaCanXoa->data.hoTen << "\n";
                delete toaCanXoa; soNguoiBiXoa++;
            } else p = p->next; 
        }
    }
    if (soNguoiBiXoa == 0) cout << "=> Khong co SV nao bi qua 2 loi.\n";
    else {
        cout << "=> Da xoa tong cong " << soNguoiBiXoa << " sinh vien.\n";
        ghiFileSinhVien();
    }
}

void menuSinhVien() {
    int chon;
    bool quayLai = false;
    
    static bool daDocFile = false;
    if (!daDocFile) {
        docFileSinhVien();
        daDocFile = true;
    }

    while (!quayLai) {
        cout << "\n============= QUAN LY SINH VIEN =============\n";
        cout << "1. Them ho so moi\n";
        cout << "2. In danh sach sinh vien\n";
        cout << "3. Tim kiem ho so theo Ma SV\n";
        cout << "4. Sua thong tin sinh vien\n";
        cout << "5. Ghi nhan vi pham ky luat\n";
        cout << "6. Xoa sinh vien vi pham (Tu 3 loi tro len)\n";
        cout << "7. Luu toan bo du lieu xuong file text\n";
        cout << "0. Quay lai menu chinh\n";
        cout << "---------------------------------------------\n";
        cout << "Chon chuc nang: ";
        cin >> chon;
        
        switch (chon) {
            case 1: themSinhVien(); break;
            case 2: inDanhSachSinhVien(); break;
            case 3: timKiemSinhVien(); break;
            case 4: suaThongTinSinhVien(); break;
            case 5: ghiNhanViPham(); break;
            case 6: xoaSinhVienViPham(); break;
            case 7: ghiFileSinhVien(); break;
            case 0: quayLai = true; break;
            default: cout << "Loi! Vui long chon lai.\n"; break;
        }
    }
}