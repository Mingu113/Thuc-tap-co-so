#include <iostream>
#include "KhachHang.h"
#include "GiaoDich.h"
using namespace std;
// Khai báo struct

// Hàm main
int main()
{
	// Chỉnh timezone sang Việt Nam
	// putenv("TZ=Asia/Vietnam");
	DocGDtuFile();
	DocKHtuFile();
	Menu();
	fflush(stdin);
	getchar();
	system("cls");
}

void Menu()
{
	fflush(stdin);
	system("cls");
Menu:
	cout << "..............................." << endl;
	cout << "Xu ly giao dich ngan hang don gian\n";
	cout << "Chon chuc nang can thuc hien: \n";
	cout << "[1] Quan ly khach hang\n";
	cout << "[2] Thuc hien giao dich\n";
	cout << "[3] Thoat\n";
	cout << "Nhap mot so: ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
	system("cls");
		Menu_KhachHang();

		fflush(stdin);
		getchar();
		goto Menu;
		break;
	case 2:
		fflush(stdin);
		system("cls");

		ThucHienGD();

		fflush(stdin);
		getchar();
		goto Menu;
		break;
	case 3:
		return;
	default:
		goto Menu;
		break;
	}
}
void Menu_KhachHang()
{
	fflush(stdin);
	system("cls");
Menu:
	cout << "..............................." << endl;
	cout << "Quan ly khach hang:\n"
		 << "Chon chuc nang can thuc hien:\n";
	cout << "[1] Them Khach hang" << endl;
	cout << "[2] Xoa Khach hang" << endl;
	cout << "[3] In Danh sach khach hang\n";
	cout << "[4] In sao ke giao dich\n";
	cout << "[5] In toan bo giao dich\n";
	cout << "[6] Thoat\n";

	cout << "Nhap mot so: ";
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		fflush(stdin);
		system("cls");

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

		getchar();
		goto Menu;
		break;
	case 3:
		fflush(stdin);
		system("cls");

		InDSKH();

		getchar();
		goto Menu;
		break;
	case 4:
		fflush(stdin);
		system("cls");

		SaoKe();

		getchar();
		break;
	case 5:
		fflush(stdin);
		system("cls");

		SaoKe(true);

		getchar();
	case 6:
		return;
	default:
		goto Menu;
		break;
	}
}