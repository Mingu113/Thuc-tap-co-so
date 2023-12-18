#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "KhachHang.h"
using namespace std;
// Đường dẫn tập tin khách hàng
const char *PathCustomer = "customer.dat";

bool operator==(const KhachHang &a, const KhachHang &b)
{
	return strcmp(a.MaKH, b.MaKH) == 0 ? true : false;
};

bool ThemKH(KhachHang kh)
{
	for (int i = 0; i < DSKhachHang.size(); i++)
		if (strcmp(kh.MaKH, DSKhachHang[i].MaKH) == 0)
			return false;
	DSKhachHang.push_back(kh);
	GhiKHvaoFile();
	return true;
}

KhachHang ThemKHtuBP()
{
	KhachHang kh;
	// Lấy mã khách hàng của khách hàng cuối cùng trong danh sách khách hàng, +1
	itoa(atoi(DSKhachHang[DSKhachHang.size()].MaKH) + 1, kh.MaKH, 10);
	cout << "Nhap ten khach hang: ";
	fflush(stdin);
	gets(kh.TenKH);
	cout << "Nhap so du khach hang: ";
	fflush(stdin);
	cin >> kh.sodu;
	return kh;
}

void InKH(KhachHang kh)
{
	cout << left << "|" << setw(6) << kh.MaKH
		 << "|" << setw(19) << kh.TenKH
		 << "|" << setw(22) << fixed << setprecision(2) << kh.sodu << setw(4) << "VND" << "|" << endl;
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
		if (i == 0)
			cout << "_______________________________________________________\n"
					"|  Ma  |   Ten Khach hang  |      So tien             |\n"
					"|______|___________________|__________________________|\n";
		InKH(DSKhachHang[i]);
		if (i == DSKhachHang.size() - 1)
			cout << "|______|___________________|__________________________|\n";
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

void XuatSangCSV_KH()
{
	char FileName[] = "KhachHang.csv";
	ofstream file(FileName);
	// Viết CSV header
	file << "Ma KH, Ten KH, So du" << endl;
	/// Xuất nội dung
	for (auto &kh : DSKhachHang)
	{
		file << kh.MaKH << ", " << kh.TenKH << ", " << fixed << setprecision(2) << kh.sodu << endl;
	}
	file.close();
	cout << "Da xuat danh sach khach hang vao file: " << FileName << endl;
}