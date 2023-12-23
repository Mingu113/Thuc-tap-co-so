#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cctype>
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
void wait(int sec)
{
	time_t timer = time(NULL) + sec;
	while (time(NULL) < timer)
	{
	}
	return;
}
KhachHang ThemKHtuBP()
{
	KhachHang kh;
	// Lấy mã khách hàng của khách hàng cuối cùng trong danh sách khách hàng, +1
	itoa(atoi(DSKhachHang.back().MaKH) + 1, kh.MaKH, 10);
	// -> Không biết vì sao thêm khách hàng lần 2 thì danh sách khách hàng lại bị trống,
	// mã khách hàng về lại 1
	cout << "Ma khach hang: " << kh.MaKH << endl;
	cout << "Nhap ten khach hang: ";
	fflush(stdin);
	cin.getline(kh.TenKH, sizeof(kh.TenKH));
	cout << "Nhap so du khach hang: ";
	fflush(stdin);
	cin >> kh.sodu;
	kh.TrangThai = true;
	return kh;
}

void InKH(KhachHang kh)
{
	cout << left << "|" << setw(6) << kh.MaKH
		 << "|" << setw(19) << kh.TenKH
		 << "|" << setw(22) << fixed << setprecision(2) << kh.sodu << setw(4) << "VND"
		 << "|" << setw(15) << (kh.TrangThai == true ? "Da kich hoat" : "Da khoa")
		 << "|" << endl;
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

void InDSKH(bool TrangThai)
{
#pragma omp critical(InDSKH)
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		if (i == 0)
			cout << "_______________________________________________________________________\n"
					"|  Ma  |   Ten Khach hang  |      So tien             |   Trang thai  |\n"
					"|______|___________________|__________________________|_______________|\n";
		if (TrangThai)
		{
			if (DSKhachHang[i].TrangThai)
				InKH(DSKhachHang[i]);
		}
		else
		{
			if (!DSKhachHang[i].TrangThai)
				InKH(DSKhachHang[i]);
		}
		if (i == DSKhachHang.size() - 1)
			cout << "|______|___________________|__________________________|_______________|\n";
	}
	// Độ phức tạp cao
}

bool KhoaKH(char *MaKH)
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
		DSKhachHang[pos].TrangThai = false;
		GhiKHvaoFile();
		cout << "Da khoa tai khoan khach hang " << DSKhachHang[pos].TenKH << endl;
		cout << "_______________________________________________________________________\n"
				"|  Ma  |   Ten Khach hang  |      So tien             |   Trang thai  |\n"
				"|______|___________________|__________________________|_______________|\n";
		InKH(DSKhachHang[pos]);
		cout << "|______|___________________|__________________________|_______________|\n";
		return true;
	}
	return false;
}
bool MoKhoaKH(char *MaKH)
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
		DSKhachHang[pos].TrangThai = true;
		GhiKHvaoFile();
		cout << "Da mo khoa tai khoan khach hang " << DSKhachHang[pos].TenKH << endl;
		cout << "_______________________________________________________________________\n"
				"|  Ma  |   Ten Khach hang  |      So tien             |   Trang thai  |\n"
				"|______|___________________|__________________________|_______________|\n";
		InKH(DSKhachHang[pos]);
		cout << "|______|___________________|__________________________|_______________|\n";
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
			DSKhachHang[i].TrangThai = kh.TrangThai;
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
	file << "Ma KH, Ten KH, So du, Trang thai tai khoan" << endl;
	/// Xuất nội dung
	for (auto &kh : DSKhachHang)
	{
		string temp = (kh.TrangThai) ? "Da kich hoat" : "Da khoa";
		file << kh.MaKH << ", " << kh.TenKH << ", " << fixed << setprecision(2) << kh.sodu << "," << temp << endl;
	}
	file.close();
	cout << "Da xuat danh sach khach hang vao file: " << FileName << endl;
	wait(5);
}
void ToLowercase(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		str[i] = tolower(str[i]);
	}
}
void TimKiemDSKH()
{
	// Hien thi lua chon
	cout << "Tim kiem khach hang: " << endl;
	cout << "___________________________" << endl;
	cout << "|Tim kiem khach hang theo:| " << endl;
	cout << "|-------------------------|" << endl;
	cout << left << "|" << setw(5) << "[1]" << setw(20) << "Ten"
		 << "|" << endl
		 << "|" << setw(5) << "[2]" << setw(20) << "Ma"
		 << "|" << endl;
	cout << "|_________________________|" << endl;
	cout << "Chon mot so: ";
	int choice;
	cin >> choice;
	// Thuc hien viec tim kiem sau khi chon
	KhachHang kh;
	char Ma[sizeof(kh.MaKH)];
	char Ten[sizeof(kh.TenKH)];
	switch (choice)
	{
	case 1:
		cout << "Nhap ten khach hang can tim: ";
		fflush(stdin);
		cin.getline(Ten, sizeof(Ten));
		ToLowercase(Ten);
		char *found;
		char temp[sizeof(kh.TenKH)];
		cout << "_______________________________________________________________________\n"
				"|  Ma  |   Ten Khach hang  |      So tien             |   Trang thai  |\n"
				"|______|___________________|__________________________|_______________|\n";
#pragma omp critical(TimKiemDSKH)
		for (auto &khach : DSKhachHang)
		{
			strcpy(temp, khach.TenKH);
			ToLowercase(temp);
			found = strstr(temp, Ten);
			if (found)
				InKH(khach);
		}
		break;
	case 2:
		cout << "Nhap ma khach hang can tim: ";
		cin >> Ma;
		cout << "_______________________________________________________________________\n"
				"|  Ma  |   Ten Khach hang  |      So tien             |   Trang thai  |\n"
				"|______|___________________|__________________________|_______________|\n";
		for (auto &khach : DSKhachHang)
		{
			if (strcmp(Ma, khach.MaKH) == 0)
				InKH(khach);
		}
		break;
	default:
		break;
	}
	cout << "|______|___________________|__________________________|_______________|\n";
	return;
}