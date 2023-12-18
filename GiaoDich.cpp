#include <iostream>
#include <stdlib.h>
#include <locale>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "GiaoDich.h"
#include "KhachHang.h"
using namespace std;
// Đường dẫn tập tin giao dịch
const char *PathTransaction = "transaction.dat";
vector<KhachHang> DSKhachHang;
vector<GiaoDich> DSGiaoDich;
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
	GiaoDich gd;
	KhachHang kh;
	char TienGD[1024];
NhapMa:
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
			cout << "Khach hang: " << kh.TenKH << endl;
			goto NhapLoaiGD;
			break;
		}
	}
	cout << "Khong tim thay ma khach hang" << endl;
	goto NhapMa;
// Nhập loại giao dịch
NhapLoaiGD:
	int LoaiGD;
	string GD_Type[] = {"Rut tien", "Gui tien", "Huy"};
	for (int i = 0; i < GD_Type->size(); i++)
	{
		cout << GD_Type[i] << endl;
	}
	cout << "Chon loai giao dich: ";
	fflush(stdin);
	cin >> LoaiGD;
	if (LoaiGD >= 1 && LoaiGD <= 2)
		gd.LoaiGD = LoaiGD;
	else if (LoaiGD == 3)
		return;
	else
	{
		cout << "Nhap lai loai giao dich";
		goto NhapLoaiGD;
	}
	cout << "Loai giao dich: " << GD_Type[LoaiGD - 1] << endl;
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
	return;
}

void InGD(GiaoDich gd)
{
	char buffer[32];
	tm ThoiGian;
	localtime_s(&ThoiGian, &gd.NgayGD);
	strftime(buffer, sizeof(buffer), "%H:%M %d/%m/%Y ", &ThoiGian);
	cout << left << "|" << setw(9) << gd.MaGD
		 << "|" << setw(10) << gd.MaKH
		 << "|" << setw(25) << fixed << setprecision(2) << gd.LuongTien << setw(4) << "VND"
		 << "|" << setw(12) << (gd.LoaiGD == 1 ? "Rut tien" : "Gui tien")
		 << "|" << setw(22) << fixed << setprecision(2) << gd.SoDu << setw(4) << "VND"
		 << "|" << setw(25) << buffer << "|" << endl;
}

void SaoKe(bool InToanBo)
{
	bool temp = false;
	if (!InToanBo)
	{
		char Ma[4];
		cout << "Nhap ma khach hang can lap sao ke ";
		fflush(stdin);
		cin >> Ma;
#pragma omp parallel for
		for (int i = 0; i < DSGiaoDich.size(); i++)
		{
			if (i == 0)
				cout << "______________________________________________________________________________________________________________________\n"
						"|  Ma GD  |   Ma KH  |      Giao dich              |   Loai GD  |      So du hien tai      |    Thoi gian giao dich  |\n"
						"|_________|__________|_____________________________|____________|__________________________|_________________________|\n";

			if (strcmp(DSGiaoDich[i].MaKH, Ma) == 0)
			{
				temp = true;
				InGD(DSGiaoDich[i]);
			}
		}
	}
	else
	{
		cout << "______________________________________________________________________________________________________________________\n"
				"|  Ma GD  |   Ma KH  |      Giao dich              |   Loai GD  |      So du hien tai      |    Thoi gian giao dich  |\n"
				"|_________|__________|_____________________________|____________|__________________________|_________________________|\n";
		temp = true;
#pragma omp parallel for
		for (int i = 0; i < DSGiaoDich.size(); i++)
			InGD(DSGiaoDich[i]);
	}

	if (!temp)
		cout << "Khong co giao dich nao\n";
	else
		cout << "|_________|__________|_____________________________|____________|__________________________|_________________________|\n";
}

void XuatSangCSV_GD()
{
	char FileName[] = "GiaoDich.csv";
	ofstream file(FileName);
	// Viết CSV header
	file << "Ma GD, MaKH, Luong Tien, Loai GD,So du hien tai,Thoi gian giao dich" << endl;
	char buffer[32];
	tm ThoiGian;
	for (auto &gd : DSGiaoDich)
	{
		localtime_s(&ThoiGian, &gd.NgayGD);
		strftime(buffer, sizeof(buffer), "%H:%M %d/%m/%Y ", &ThoiGian);
		file << gd.MaGD << "," << gd.MaKH << "," << fixed << setprecision(2) << gd.LuongTien
			 << "," << gd.LoaiGD << "," << fixed << setprecision(2) << gd.SoDu << "," << buffer << endl;
	}
	file.close();
	cout << "Da xuat giao dich vao file: " << FileName << endl;
}