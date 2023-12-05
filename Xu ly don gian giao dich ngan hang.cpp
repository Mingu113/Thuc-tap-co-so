#define _XOPEN_SOURCE = 700 // cho putenv
#include <iostream>
#include <stdlib.h> // cho putenv
#include <time.h>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;
// Đường dẫn tập tin khách hàng
const char *PathCustomer = "customer.dat";
// Đường dẫn tập tin giao dịch
const char *PathTrans = "trans.dat";
// Khai báo struct

// struct Khách hàng
typedef struct
{
	char MaKH[4];
	char TenKH[50];
	int sodu;
} KhachHang;

// struct Giao dịch
typedef struct
{
	char ID[5];
	char MaKH[4];
	int LuongTien;
	bool RutTien;
	time_t NgayGD;
} GiaoDich;
// Vector Danh sách khách hàng
vector<KhachHang> DSKhachHang;

// Vector Danh sách giao dịch
vector<GiaoDich> DSGiaoDich;
// Khai báo hàm

// Ghi danh sách khách hàng vào file
void GhiKHvaoFile();

// Thêm Khách hàng
bool ThemKH(KhachHang kh);

// Xoá Khách hàng từ mã khách hàng
bool XoaKH(char *MaKH);

// Cập nhật khách hàng từ mã khách hàng
bool CapNhatKH(KhachHang kh);

// In Khách hàng
void InKH(KhachHang kh);

// In danh sách khách hàng hiện tại
void InDSKH();

// so sánh hai khách hàng bằng mã khách hàng
bool operator==(const KhachHang &a, const KhachHang &b)
{
	return strcmp(a.MaKH, b.MaKH) == 0 ? true : false;
};

// Hàm main
int main()
{
	// Chỉnh timezone sang Việt Nam
	putenv("TZ=Asia/Vietnam");
}
// Hàm

bool ThemKH(KhachHang kh)
{
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		if (strcmp(kh.MaKH, DSKhachHang[i].MaKH) == 0)
			return false;
	}
	DSKhachHang.push_back(kh);
	GhiKHvaoFile();
	return true;
}

void InKH(KhachHang kh)
{
	cout << kh.MaKH << "\n"
		 << kh.TenKH << "\n"
		 << kh.sodu << endl;
}

void GhiKHvaoFile()
{
	int size = DSKhachHang.size();
	FILE *f;
	f = fopen(PathCustomer, "wb");
	KhachHang kh;
	for (int i = 0; i < size; i++)
	{
		kh = DSKhachHang[i];
		fwrite(&kh, sizeof(KhachHang), 1, f);
	}
	fclose(f);
}

void InDSKH()
{
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		InKH(DSKhachHang[i]);
	}
}

bool XoaKH(char *MaKH)
{
	int pos = -1;
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		if (strcmp(DSKhachHang[i].MaKH, MaKH) == 0)
		{
			pos = i;
			break;
		}
	}
	if (pos != -1)
	{
		DSKhachHang.erase(DSKhachHang.begin() + pos);
		GhiKHvaoFile();
		return true;
	}
	return false;
}

bool CapNhatKH(KhachHang kh)
{
	bool complete = false;
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		if (DSKhachHang[i] == kh)
		{
			complete = true;
			DSKhachHang[i].sodu = kh.sodu;
			strcpy(DSKhachHang[i].MaKH, kh.MaKH);
			strcpy(DSKhachHang[i].TenKH, kh.TenKH);
		}
	}
	if (!complete)
		return false;
	else
		return true;
}