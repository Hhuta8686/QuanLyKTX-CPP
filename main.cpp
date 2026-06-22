#include <iostream>
#include "SinhVien.h"
#include "Phong.h"
#include "DangKy.h"
#include "HoaDon.h"
#include "ThongKe.h" 

using namespace std;

int main() {
    int chon;
    bool thoat = false;

    while (!thoat) {
        cout << "\n==================================================\n";
        cout << "    HE THONG QUAN LY KY TUC XA BACH KHOA HA NOI   \n";
        cout << "==================================================\n";
        cout << "1. Quan ly Sinh Vien\n";
        cout << "2. Quan ly Phong KTX\n";
        cout << "3. Quan ly Thue phong (Dang ky, Chuyen, Gia han)\n";
        cout << "4. Quan ly Hoa don (Dien, Nuoc, Tien phong)\n";
        cout << "5. Bao cao & Thong ke\n"; 
        cout << "0. Thoat chuong trinh\n";
        cout << "--------------------------------------------------\n";
        cout << "Chon module chuc nang: ";
        cin >> chon;

        switch (chon) {
            case 1:
                menuSinhVien(); 
                break;
            case 2:
                menuPhong();   
                break;
            case 3:
                menuDangKy();  
                break;
            case 4:
                menuHoaDon();  
                break;
            case 5:
                menuThongKe();  
                break;
            case 0:
                cout << "\n=> Da thoat he thong. Cam on ban da su dung phan mem!\n";
                thoat = true;
                break;
            default:
                cout << "[LOI] Lua chon khong hop le! Vui long nhap tu 0 den 5.\n";
                break;
        }
    }

    return 0;
}



