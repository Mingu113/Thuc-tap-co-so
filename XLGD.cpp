#include <iostream>
#include"KhachHang.h"
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