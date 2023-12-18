#include <iostream>
#include "KhachHang.h"
#include "GiaoDich.h"
using namespace std;
// Khai báo struct

// Hàm main
int main()
{
	DocGDtuFile();
	DocKHtuFile();
	Menu();
	fflush(stdin);
	getchar();
	system("cls");
}

void Menu()
{
Menu:
	system("cls");
	string Title[] = {"Xu ly giao dich ngan hang don gian", "Chon chuc nang can thuc hien: "};
	string Menu[] = {"Quan ly khach hang va giao dich", "Thuc hien giao dich"};
	for (int i = 0; i < size(Title); i++)
	{
		cout << Title[i] << endl;
	}
	for (int i = 0; i < size(Menu); i++)
	{
		printf("[%d] ", i + 1);
		cout << Menu[i] << endl;
	}
	printf("[%d] ", size(Menu) + 1);
	cout << "Thoat" << endl;
	cout << "Nhap mot so: ";
	int choice;
	fflush(stdin);
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Quan ly khach hang va giao dich: " << endl;
		Menu_KhachHang();

		fflush(stdin);
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
		"Xoa Khach hang",
		"In danh sach khach hang",
		"In sao ke giao dich",
		"In toan bo giao dich",
		"Xuat giao dich sang .CSV",
	};
	for (int i = 0; i < size(Menu); i++)
	{
		printf("[%d] ", i + 1);
		cout << Menu[i] << endl;
	}
	printf("[%d] ", size(Menu) + 1);
	cout << "Thoat" << endl;
	int choice;
	cout << "Nhap mot so: ";
	fflush(stdin);
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
		gets(Ma);
		XoaKH(Ma);

		fflush(stdin);
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
		fflush(stdin);
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
		XuatSangCSV();
		fflush(stdin);
		getchar();
		goto Menu;
	case size(Menu) + 1:
		return;
	default:
		goto Menu;
		break;
	}
}