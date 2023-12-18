#include <iostream>
#include "KhachHang.h"
#include "GiaoDich.h"
#include <omp.h>
using namespace std;
// Nguyễn Hoàng Minh

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
		cout << Title[i] << endl;
	int i = 0;
	while (i <= size(Menu))
	{
		if (i == size(Menu))
		{
			printf("[%d] ", i + 1);
			cout << "Thoat" << endl;
			cout << "Nhap mot so: ";
			break;
		}
		printf("[%d] ", i + 1);
		cout << Menu[i] << endl;
		i++;
	}
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
		"Xoa Khach hang",
		"In danh sach khach hang",
		"In sao ke giao dich",
		"In toan bo giao dich",
		"Xuat lich su giao dich sang .CSV",
		"Xuat danh sach khach hang sang .CSV"};
	int i = 0;
	while (i <= size(Menu))
	{
		if (i == size(Menu))
		{
			printf("[%d] ", ++i);
			cout << "Thoat\n"
				 << "Nhap mot so: ";
			break;
		}
		printf("[%d] ", i + 1);
		cout << Menu[i] << endl;
		i++;
	}
	int choice;
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
		fflush(stdin);
		getchar();
		goto Menu;
	case 7:
		XuatSangCSV_KH();
		fflush(stdin);
		getchar();
		break;
	case size(Menu) + 1:
		return;
		break;
	default:
		goto Menu;
		break;
	}
}