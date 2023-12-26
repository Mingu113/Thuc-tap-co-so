#pragma once
#ifndef KHACHHANG_H
#define KHACHHANG_H
#include<vector>
// struct Khách hàng gồm Mã khách hàng, tên khách hàng, số dư, trạng thái
typedef struct
{
	char MaKH[4];	// Mã Khách hàng [4]
	char TenKH[50]; // Tên khách hàng [5]
	float sodu;		// Số dư tài khoản float
	bool TrangThai; // Trạng thái tài khoản, true nếu được kích hoạt, false nếu bị khoá
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

// Khoá Khách hàng từ mã khách hàng, trả về true sau khi hoàn thành
bool KhoaKH(char *MaKH);
// Mở khoá tài khoản khách hàng, trả về true sau khi hoàn thành
bool MoKhoaKH(char *MaKH);

// Cập nhật khách hàng từ mã khách hàng, trả về true sau khi hoàn thành
bool CapNhatKH(KhachHang kh);

// In Khách hàng
void InKH(KhachHang kh);

// In danh sách khách hàng hiện tại, true để in tài khoản đã kích hoạt, false để in tài khoản đã bị khoá
void InDSKH(bool TrangThai);
// So sánh hai khách hàng bằng mã khách hàng
bool operator==(const KhachHang &a, const KhachHang &b);

// In danh sách khách hàng sang một file csv
void XuatSangCSV_KH();

// Tìm kiếm và hiển thị các khách hàng trong danh sách
void TimKiemDSKH();
#endif