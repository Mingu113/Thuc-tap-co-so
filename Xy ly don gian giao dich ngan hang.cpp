#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;
// Duong dan
const char *PathCustomer = "customer.dat";
const char *PathTrans = "trans.dat";
// Khai báo struct
typedef struct
{
	char MaKH[4];
	string TenKH;
	int sodu;
} KhachHang;
typedef struct
{
	char MaKH[4];
	int LuongTien;
} GiaoDich;
vector<KhachHang> DSKhachHang;
vector<GiaoDich> DSGiaoDich;
// Khai báo hàm
KhachHang NhapKH();
KhachHang ThemKH(const char ma[4], string ten, int sodu);
GiaoDich TaoGiaoDich(const char ma[4], int tien, string loai);
bool operator==(const KhachHang &a, const KhachHang &b)
{
	return strcmp(a.MaKH, b.MaKH) == 0 ? true : false;
};
vector<KhachHang> NhapDSKH();
vector<GiaoDich> NhapDSGD();
void InKH(KhachHang kh);
void ThucHienGiaoDich(KhachHang kh, int money, string LoaiGD);
void NhapKHVaoFile(vector<KhachHang> DSKH);
void GhiGDVaoFile(vector<GiaoDich> DSGiaoDich);
void DocGiaoDich(vector<GiaoDich> DSGiaoDich);
void InGD(GiaoDich gd);
void InDSKH(vector<KhachHang> DSKhachHang);
// Hàm main
int main()
{
	KhachHang kh1 = ThemKH("001", "Nguyen Van A", 1000000);
	KhachHang kh2 = ThemKH("002", "Tran Van B", 200000);
	DSKhachHang.push_back(kh1);
	DSKhachHang.push_back(kh2);
	NhapKHVaoFile(DSKhachHang);
	DSKhachHang.clear();
	DSKhachHang = NhapDSKH();
	InDSKH(DSKhachHang);
	ThucHienGiaoDich(kh1, 500000, "rut tien");
	ThucHienGiaoDich(kh2, 2000000, "gui tien");
	DSGiaoDich.clear();
	DSGiaoDich = NhapDSGD();
	DocGiaoDich(DSGiaoDich);
	InDSKH(DSKhachHang);
	int a;
	cin >> a;
}
// Hàm
KhachHang ThemKH(const char ma[4], string ten, int sodu)
{
	KhachHang kh;
	strcpy(kh.MaKH, ma);
	kh.TenKH = ten;
	kh.sodu = sodu;
	return kh;
}
KhachHang NhapKH()
{
	KhachHang kh;
	cout << "Nhap ma khach hang: ";
	cin >> kh.MaKH;
	cout << "Nhap ten khach hang: ";
	cin >> kh.TenKH;
	cout << "Nhap so du: ";
	cin >> kh.sodu;
	return kh;
}
void InKH(KhachHang kh)
{
	cout << "Ma: " << kh.MaKH << ", Ten: " << kh.TenKH << ", So du: " << kh.sodu << endl;
}
vector<KhachHang> NhapDSKH()
{
	vector<KhachHang> DS;
	FILE *f;
	f = fopen(PathCustomer, "rb");
	if (f != NULL)
	{
		while (!feof(f))
		{
			KhachHang kh;
			fread(&kh, sizeof(kh), 1, f);
			DS.push_back(kh);
		}
		fclose(f);
		DS.pop_back();
	}
	return DS;
}
GiaoDich TaoGiaoDich(const char ma[4], int tien)
{
	GiaoDich gd;
	strcpy(gd.MaKH, ma);
	gd.LuongTien = tien;
	return gd;
}
vector<GiaoDich> NhapDSGD()
{
	vector<GiaoDich> DS;
	FILE *f;
	f = fopen(PathTrans, "rb");
	if (f != NULL)
		while (!feof(f))
		{
			GiaoDich gd;
			fread(&gd, sizeof(GiaoDich), 1, f);
			DS.push_back(gd);
		}
	fclose(f);
	DS.pop_back();
	return DS;
}
void GhiGDVaoFile(vector<GiaoDich> DSGiaoDich)
{
	FILE *f;
	f = fopen(PathTrans, "wb");
	GiaoDich gd;
	for (int i = 0; i < DSGiaoDich.size(); i++)
	{
		gd = DSGiaoDich[i];
		fwrite(&gd, sizeof(GiaoDich), 1, f);
	}
	fclose(f);
}
void ThucHienGiaoDich(KhachHang kh, int money, string LoaiGD)
{
	bool HoanThanh = false;
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		if (DSKhachHang[i] == kh)
		{
			GiaoDich gd;
			if (LoaiGD.compare("rut tien") == 0)
			{
				DSKhachHang[i].sodu -= money;
				gd = TaoGiaoDich(kh.MaKH, money * -1);
			}
			else
			{
				DSKhachHang[i].sodu += money;
				gd = TaoGiaoDich(kh.MaKH, money);
			}
			DSGiaoDich.push_back(gd);
			GhiGDVaoFile(DSGiaoDich);
			NhapKHVaoFile(DSKhachHang);
			HoanThanh = true;
			break;
		}
	}
	if (HoanThanh == false)
		cout << "Giao dich that bai" << endl;
}
void InGD(GiaoDich gd)
{
	cout
		<< "Ma: " << gd.MaKH << ", Luong tien: "
		<< (gd.LuongTien < 0 ? gd.LuongTien * -1 : gd.LuongTien)
		<< ", Loai GD: " << (gd.LuongTien < 0 ? "rut tien" : "gui tien")
		<< endl;
}
void DocGiaoDich(vector<GiaoDich> DSGiaoDich)
{
	for (size_t i = 0; i < DSGiaoDich.size(); i++)
	{
		InGD(DSGiaoDich[i]);
	}
}
void InDSKH(vector<KhachHang> DSKhachHang)
{
	for (size_t i = 0; i < DSKhachHang.size(); i++)
	{
		InKH(DSKhachHang[i]);
	}
}
void NhapKHVaoFile(vector<KhachHang> DSKhachHang)
{
	FILE *f;
	f = fopen(PathCustomer, "wb");
	KhachHang kh;
	for (int i = 0; i < DSKhachHang.size(); i++)
	{
		kh = DSKhachHang[i];
		fwrite(&kh, sizeof(KhachHang), 1, f);
	}
	fclose(f);
}
