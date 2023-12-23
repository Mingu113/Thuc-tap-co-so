#include <iostream>
#include "KhachHang.h"
#include "GiaoDich.h"
#include <omp.h>
#include <iomanip>
using namespace std;
// Nguyễn Hoàng Minh

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
		"Khoa/Mo tai khoan Khach hang",
		"Hien thi danh sach khach hang",
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
		cout << "Khoa hoac kich hoat tai khoan khach hang:\n";
		cout << "_______________________" << endl;
		cout << left
			 << "|" << setw(3) << "1"
			 << "|" << setw(17) << "Khoa"
			 << "|" << endl
			 << "|" << setw(3) << "2"
			 << "|" << setw(17) << "Kich hoat"
			 << "|" << endl;
		cout << "|___|_________________|" << endl;
		cout << "Nhap mot so: ";
		cin >> choice;
		char Ma[4];
		switch (choice)
		{
		case 1:
			cout << "Nhap ma khach hang: ";
			fflush(stdin);
			cin.getline(Ma, sizeof(Ma));
			KhoaKH(Ma);
			break;
		case 2:
			cout << "Nhap ma khach hang: ";
			fflush(stdin);
			cin.getline(Ma, sizeof(Ma));
			MoKhoaKH(Ma);
		default:
			break;
		}
		getchar();
		goto Menu;
		break;
	case 3:
		cout << "Hien thi danh sach khach hang:\n";
		cout << "_______________________" << endl;
		cout << left
			 << "|" << setw(3) << "1"
			 << "|" << setw(17) << "Da kich hoat"
			 << "|" << endl
			 << "|" << setw(3) << "2"
			 << "|" << setw(17) << "Da khoa"
			 << "|" << endl;
		cout << "|___|_________________|" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			InDSKH(true);
			break;
		case 2:
			InDSKH(false);
			break;
		default:
			return;
		}
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