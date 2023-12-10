#ifndef KHACHHANG_H
#define KHACHHANG_H
#include<vector>
// struct Khách hàng gồm Mã khách hàng, tên khách hàng, số dư
typedef struct
{
	char MaKH[4];	// Mã Khách hàng [4]
	char TenKH[50]; // Tên khách hàng [5]
	float sodu;		// Số dư tài khoản float
} KhachHang;
// Vector Danh sách khách hàng
extern std::vector<KhachHang> DSKhachHang;

// Ghi danh sách khách hàng vào file
void GhiKHvaoFile();

// Đọc danh sách khách hàng từ file
void DocKHtuFile();

// Thêm Khách hàng, trả về true sau khi hoàn thành
bool ThemKH(KhachHang kh);

// Nhập khách hàng từ bàn phím, trả về struct kiểu khách hàng
KhachHang ThemKHtuBP();

// Xoá Khách hàng từ mã khách hàng, trả về true sau khi hoàn thành
bool XoaKH(char *MaKH);

// Cập nhật khách hàng từ mã khách hàng, trả về true sau khi hoàn thành
bool CapNhatKH(KhachHang kh);

// In Khách hàng
void InKH(KhachHang kh);

// In danh sách khách hàng hiện tại
void InDSKH();
// So sánh hai khách hàng bằng mã khách hàng
bool operator==(const KhachHang &a, const KhachHang &b);

#endif