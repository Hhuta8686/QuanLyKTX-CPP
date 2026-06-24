# 🏢 HỆ THỐNG QUẢN LÝ KÝ TÚC XÁ 

Hệ thống quản lý thông tin nội trú Ký túc xá được viết bằng ngôn ngữ **C++** theo kiến trúc **Modular**, sử dụng cấu trúc dữ liệu **Danh sách liên kết đơn (Singly Linked List)** để tối ưu hóa bộ nhớ và quản lý dữ liệu động toàn cục.

---

## 🛠️ Các Chức Năng Chính Của Hệ Thống

### 1. Quản lý Sinh viên
* **Thêm hồ sơ**: Hỗ trợ kiểm tra trùng mã SV, bắt buộc điền đầy đủ thông tin liên lạc và diện ưu tiên.
* **Xử lý kỷ luật**: Ghi nhận số lần vi phạm và tự động xóa tên (buộc thôi ở) nếu vi phạm từ 3 lần trở lên.
* **Tìm kiếm & Chỉnh sửa**: Tra cứu thông tin hồ sơ nhanh chóng qua Mã SV.

### 2. Quản lý Phòng KTX
* **Phân loại giường**: Hệ thống hỗ trợ 3 loại phòng tiêu chuẩn: 4 giường, 6 giường và 8 giường.
* **Tự động áp đơn giá**: Giá thuê phòng tính tự động theo kỳ học dựa trên loại phòng được chọn.
* **Kiểm soát trạng thái**: Tự động khóa phòng khi số người hiện tại đạt tối đa (HẾT CHỖ).

### 3. Quản lý Thuê phòng & Chuyển phòng
* **Ràng buộc giới tính**: Tự động kiểm tra giới tính của phòng, đảm bảo không xếp sinh viên nam và nữ ở chung phòng.
* **Điều chuyển linh hoạt**: Hỗ trợ chuyển phòng nhanh, tự động trừ sĩ số phòng cũ và cộng sĩ số phòng mới trên RAM.

### 4. Quản lý Hóa đơn Điện - Nước
* **Chia đều tự động**: Nhập chỉ số điện/nước của cả phòng, hệ thống tự động chia đều tiền cho số thành viên đang ở thực tế và phát sinh hóa đơn riêng cho từng người.
* **Gạch nợ**: Quản lý trạng thái thanh toán hóa đơn cá nhân trực quan.

### 5. Báo cáo & Thống kê Số liệu
* Thống kê tỷ lệ lấp đầy (%) của từng phòng KTX.
* Xuất danh sách sinh viên vi phạm kỷ luật.
* Liệt kê danh sách sinh viên **Chưa đóng tiền phòng/điện nước** kèm mã hóa đơn thu tiền.

---

## 📁 Sơ đồ Kiến trúc Modular Dự án

```text
               [ main.cpp ]  (Hàm chạy chính & Menu điều hướng gốc)
                    │
   ┌────────────────┼────────────────┬────────────────┐
   ▼                ▼                ▼                ▼
[SinhVien]       [Phong]         [DangKy]         [HoaDon]       [ThongKe]
├── SinhVien.h   ├── Phong.h     ├── DangKy.h     ├── HoaDon.h   └── ThongKe.h
└── SinhVien.cpp └── Phong.cpp   └── DangKy.cpp   └── HoaDon.cpp └── ThongKe.cpp
