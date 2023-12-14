#ifndef GIAODICH_H
#define GIAODICH_H
#include <vector>
#include <ctime>
// struct Giao dịch gồm Mã giao dịch, mã khách hàng, lượng tiền, loại giao dịch, ngày giao dịch
typedef struct
{
	unsigned int MaGD; // Mã giao dịch tự động tăng dần theo một đơn vị
	char MaKH[4];	   // Mã khách hàng giao dịch [4]
	float LuongTien;   // Lượng tiền
	int LoaiGD;		   // 1: Rút tiền, 2: Gửi tiền
	float SoDu;		   // Số dư hiện tại sau khi giao dịch của khách hàng
	time_t NgayGD;	   // Thời gian giao dịch
} GiaoDich;
// Vector Danh sách giao dịch
std::vector<GiaoDich> DSGiaoDich; // -> KHÔNG ĐƯỢC QUÊN KHI SỬ DỤNG MỘT ĐỐI TƯỢNG NÀO ĐÓ CHO NHIỀU FILE. SỬ DỤNG EXTERN
// Ghi giao dịch vào file
void GhiGDvaoFile();

// Thêm giao dịch
bool ThemGD(GiaoDich gd);

// Đọc giao dịch  từ file
void DocGDtuFile();

// Thực hiện giao dịch
void ThucHienGD();

// In một giao dịch ra màn hình
void InGD(GiaoDich gd);

// Sao kê giao dịch của khách hàng
void SaoKe();

// Menu
void Menu();

// Menu khách hàng
void Menu_KhachHang();

#endif