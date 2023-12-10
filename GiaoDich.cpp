#define _XOPEN_SOURCE = 700 // cho putenv
#include <iostream>
#include <stdlib.h> // cho putenv
#include <time.h>
#include <cstring>
#include <fstream>
#include <algorithm>
#include "GiaoDich.h"
#include "KhachHang.h"
using namespace std;
// Đường dẫn tập tin giao dịch
const char *PathTransaction = "transaction.dat";
vector<KhachHang> DSKhachHang;
// Khai báo hàm

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