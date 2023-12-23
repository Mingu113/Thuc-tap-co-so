#include <iostream>
#include "KhachHang.h"
#include "GiaoDich.h"
#include <omp.h>
#include <iomanip>
using namespace std;
// Nguyễn Hoàng Minh
// TODO
/*
	Thêm trạng thái tài khoản
	Tìm kiếm khách hàng theo tên hoặc mã
*/

// Hàm main
int main()
{
	DocGDtuFile();
	DocKHtuFile();
	Menu();
	getchar();
	system("cls");
}

void Menu()
{
Menu:
	system("cls");
	string Title[] = {"Xu ly giao dich ngan hang don gian", "Chon chuc nang can thuc hien: "};
	string Menu[] = {"Quan ly khach hang va giao dich", "Thuc hien giao dich"};
	cout << "______________________________________________" << endl;

	for (int i = 0; i < size(Title); i++)
		cout << "|" << left << setw(44) << Title[i] << "|" << endl;
	cout << "|____________________________________________|" << endl;

	int i = 0;
	cout << "____________________________________________" << endl;

	while (i <= size(Menu))
	{
		if (i == size(Menu))
		{
			cout << left << "|" << setw(3) << i + 1 << "|";
			cout << setw(40) << "Thoat"
				 << "|" << endl;
			cout << "|___|________________________________________|" << endl;
			cout << "Nhap mot so: ";
			break;
		}
		cout << left << "|" << left << setw(3) << i + 1 << "|" << setw(40) << Menu[i] << "|" << endl;
		i++;
	}

	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Quan ly khach hang va giao dich: " << endl;
		Menu_KhachHang();

		getchar();
		goto Menu;
		break;
	case 2:
		cout << "Thuc hien giao dich: " << endl;
		ThucHienGD();
		fflush(stdin);
		getchar();
		goto Menu;
		break;
	case size(Menu) + 1:
		return;
		break;
	default:
		goto Menu;
		break;
	}
}
void Menu_KhachHang()
{
Menu:
	system("cls");
	string Menu[] = {
		"Them khach hang",
		"Khoa tai khoan Khach hang",
		"In danh sach khach hang",
		"In sao ke giao dich",
		"In toan bo giao dich",
		"Xuat lich su giao dich sang .CSV",
		"Xuat danh sach khach hang sang .CSV",
		"Tim kiem khach hang"};
	int i = 0;
	cout << "______________________________________________" << endl;
#pragma omp single
	while (i <= size(Menu))
	{
		if (i == size(Menu))
		{
			cout << left << "|" << setw(3) << i + 1 << "|"
				 << setw(40) << "Thoat"
				 << "|\n";
			cout << "|___|________________________________________|" << endl
				 << "Nhap mot so: ";
			break;
		}
		cout << left << "|" << setw(3) << i + 1 << "|" << setw(40) << Menu[i] << "|" << endl;
		i++;
	}
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		KhachHang kh;
		kh = ThemKHtuBP();
		ThemKH(kh);
		goto Menu;
		break;
	case 2:
		cout << "Nhap ma khach hang can xoa: ";
		char Ma[4];
		fflush(stdin);
		cin.getline(Ma, sizeof(Ma));
		KhoaKH(Ma);
		getchar();
		goto Menu;
		break;
	case 3:
		InDSKH();
		fflush(stdin);
		getchar();
		goto Menu;
		break;
	case 4:
		system("cls");
		SaoKe();
		fflush(stdin);
		getchar();
		goto Menu;
		break;
	case 5:
		SaoKe(true);
		fflush(stdin);
		getchar();
		goto Menu;
	case 6:
		XuatSangCSV_GD();
		getchar();
		goto Menu;
	case 7:
		XuatSangCSV_KH();
		getchar();
		goto Menu;
		break;
	case 8:
		TimKiemDSKH();
		getchar();
		goto Menu;
		break;
	case size(Menu) + 1:
		return;
		break;
	default:
		goto Menu;
		break;
	}
}