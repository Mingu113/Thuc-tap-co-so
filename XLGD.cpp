#define _XOPEN_SOURCE = 700 // cho putenv
#include <iostream>
#include <stdlib.h> // cho putenv
#include <time.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
// Đường dẫn tập tin khách hàng
const char *PathCustomer = "customer.dat";
// Đường dẫn tập tin giao dịch
const char *PathTransaction = "transaction.dat";
// Khai báo struct

// struct Khách hàng gồm Mã khách hàng, tên khách hàng, số dư
typedef struct
{
	char MaKH[4];	// Mã Khách hàng [4]
	char TenKH[50]; // Tên khách hàng [5]
	float sodu;		// Số dư tài khoản float
} KhachHang;

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
// Vector Danh sách khách hàng
vector<KhachHang> DSKhachHang;

// Vector Danh sách giao dịch
vector<GiaoDich> DSGiaoDich;
// Khai báo hàm
// Khách hàng

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
bool operator==(const KhachHang &a, const KhachHang &b)
{
	return strcmp(a.MaKH, b.MaKH) == 0 ? true : false;
};

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

// Hàm main
int main()
{
	// Chỉnh timezone sang Việt Nam
	putenv("TZ=Asia/Vietnam");
	DocGDtuFile();
	DocKHtuFile();
	Menu();
	fflush(stdin);
	getchar();
	system("cls");
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

KhachHang ThemKHtuBP()
{
	cout << "----------------------------" << endl;
	KhachHang kh;
	cout << "Nhap ma khach hang: ";
	fflush(stdin);
	gets(kh.MaKH);
	cout << "Nhap ten khach hang: ";
	fflush(stdin);
	gets(kh.TenKH);
	cout << "Nhap so du khach hang: ";
	cin >> kh.sodu;
	return kh;
}

void InKH(KhachHang kh)
{
	cout << "----------------------------" << endl;
	cout << "Ma khach hang: " << kh.MaKH << "\n"
		 << "Ten khach hang: " << kh.TenKH << "\n"
		 << "So du khach hang: " << kh.sodu << endl;
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
			GhiKHvaoFile();
			DocKHtuFile();
		}
	}
	if (!complete)
		return false;
	else
		return true;
}

void DocKHtuFile()
{
	DSKhachHang.clear();
	FILE *f;
	f = fopen(PathCustomer, "rb");
	if (f != NULL)
	{
		while (!feof(f))
		{
			KhachHang kh;
			fread(&kh, sizeof(KhachHang), 1, f);
			DSKhachHang.push_back(kh);
		}
		fclose(f);
		DSKhachHang.pop_back();
	}
}

void GhiGDvaoFile()
{
	int size = DSGiaoDich.size();
	FILE *f;
	f = fopen(PathTransaction, "wb");
	GiaoDich gd;
	for (int i = 0; i < size; i++)
	{
		gd = DSGiaoDich[i];
		fwrite(&gd, sizeof(GiaoDich), 1, f);
	}
	fclose(f);
}

void DocGDtuFile()
{
	DSGiaoDich.clear();
	FILE *f;
	f = fopen(PathTransaction, "rb");
	if (f != NULL)
	{
		while (!feof(f))
		{
			GiaoDich gd;
			fread(&gd, sizeof(GiaoDich), 1, f);
			DSGiaoDich.push_back(gd);
		}
		fclose(f);
		DSGiaoDich.pop_back();
	}
}

bool ThemGD(GiaoDich gd)
{
	DSGiaoDich.push_back(gd);
	GhiGDvaoFile();
	return true;
}

void ThucHienGD()
{
	cout << "----------------------------" << endl;
	// Tìm khách hàng theo mã
	cout << "Nhan huy de ngung" << endl;
NhapMa:
	GiaoDich gd;
	KhachHang kh;
	char TienGD[1024];
	cout << "Nhap ma khach hang: ";
	fflush(stdin);
	gets(kh.MaKH);
	// Nếu người nhập nhấn huỷ thì ngưng
	if (strcmp(kh.MaKH, "huy") == 0)
		return;
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		if (DSKhachHang[i] == kh)
		{
			kh = DSKhachHang[i];
			strcpy(gd.MaKH, kh.MaKH);
			goto NhapLoaiGD;
			break;
		}
	}
	cout << "Khong tim thay ma khach hang" << endl;
	goto NhapMa;
// Nhập loại giao dịch
NhapLoaiGD:
	int LoaiGD;
	cout << "1: Rut tien\n2: Gui tien\n3: Huy\n"
		 << "Nhap loai giao dich: ";
	cin >> LoaiGD;
	switch (LoaiGD)
	{
	case 1:
		// Rút tiền
		gd.LoaiGD = 1;
		break;
	case 2:
		// Gửi tiền
		gd.LoaiGD = 2;
		break;
	case 3:
		return;
	default:
		cout << "Nhap lai loai giao dich" << endl;
		goto NhapLoaiGD;
		break;
	}
// Nhập lượng tiền
NhapLuongTien:
	cout << "Nhap luong tien can giao dich: ";
	cin >> TienGD;
	if (strcmp(TienGD, "huy") == 0)
		return;
	if (atof(TienGD) > kh.sodu && gd.LoaiGD == 1)
	{
		cout << "Khach hang khong du tien trong tai khoan de thuc hien giao dich" << endl;
		goto NhapLuongTien;
	}
	else
	{
		gd.LuongTien = atof(TienGD);
		(gd.LoaiGD == 1) ? kh.sodu -= gd.LuongTien : kh.sodu += gd.LuongTien;
		CapNhatKH(kh);
	}
	// Thực hiện giao dịch
	gd.MaGD = DSGiaoDich.size() + 1;
	gd.NgayGD = time(NULL);
	gd.SoDu = kh.sodu;
	ThemGD(gd);
	Menu();
}

void InGD(GiaoDich gd)
{
	cout << "----------------------------" << endl;
	cout << "Ma giao dich: " << gd.MaGD << endl;
	cout << "Ma khach hang: " << gd.MaKH << endl;
	cout << "Luong tien: " << gd.LuongTien << endl;
	cout << "Loai giao dich: ";
	if (gd.LoaiGD == 1)
		cout << "Rut tien";
	else
		cout << "Gui tien";
	cout << endl;
	cout << "So du hien tai: " << gd.SoDu << endl;
	cout << "Thoi gian giao dich: " << asctime(localtime(&gd.NgayGD)) << endl;
}

void SaoKe()
{
	bool temp = false;
	cout << "Nhap ma khach hang can lap sao ke: ";
	fflush(stdin);
	char Ma[4];
	cin >> Ma;
	for (int i = 0; i < DSGiaoDich.size(); i++)
	{
		if (strcmp(DSGiaoDich[i].MaKH, Ma) == 0)
		{
			InGD(DSGiaoDich[i]);
			temp = true;
		}
	}
	if (!temp)
		cout << "Khong tim thay khach hang\n";
}

void Menu()
{
Menu:
	cout << "..............................." << endl;
	cout << "Xu ly giao dich ngan hang don gian\n";
	cout << "Chon chuc nang can thuc hien: \n";
	cout << "[1] Quan ly khach hang\n";
	cout << "[2] Thuc hien giao dich\n";
	cout << "[3] Thoat\n";
	cout << "Nhap mot so: ";
	int choice;
	fflush(stdin);
	cin >> choice;
	switch (choice)
	{
	case 1:
		fflush(stdin);
		system("cls");

		Menu_KhachHang();

		fflush(stdin);
		getchar();
		system("cls");
		goto Menu;
		break;
	case 2:
		fflush(stdin);
		system("cls");

		ThucHienGD();

		fflush(stdin);
		getchar();
		system("cls");
		goto Menu;
		break;
	case 3:
		system("cls");
		return;
	default:
		system("cls");
		goto Menu;
		break;
	}
}
void Menu_KhachHang()
{
Menu:
	cout << "..............................." << endl;
	cout << "Quan ly khach hang:\n"
		 << "Chon chuc nang can thuc hien:\n";
	cout << "[1] Them Khach hang" << endl;
	cout << "[2] Xoa Khach hang" << endl;
	cout << "[3] In Danh sach khach hang\n";
	cout << "[4] In sao ke giao dich\n";
	cout << "[5] Thoat\n";
	cout << "Nhap mot so: ";
	int choice;
	fflush(stdin);
	cin >> choice;
	switch (choice)
	{
	case 1:
		fflush(stdin);
		system("cls");

		KhachHang kh;
		kh = ThemKHtuBP();
		ThemKH(kh);

		fflush(stdin);
		system("cls");
		goto Menu;
		break;
	case 2:
		cout << "Nhap ma khach hang can xoa: ";
		char Ma[4];
		fflush(stdin);
		gets(Ma);
		XoaKH(Ma);
		
		fflush(stdin);
		getchar();
		system("cls");
		goto Menu;
		break;
	case 3:
		fflush(stdin);
		system("cls");

		InDSKH();
		
		fflush(stdin);
		getchar();
		system("cls");
		goto Menu;
		break;
	case 4:
		fflush(stdin);
		system("cls");

		SaoKe();
		
		fflush(stdin);
		getchar();
		system("cls");
		break;
	case 5:
		system("cls");
		return;
	default:
		system("cls");
		goto Menu;
		break;
	}
}