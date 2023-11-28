#include<stdio.h>
#include<vector>
#include<string.h>
#include<iostream>
using namespace std;
typedef struct
{
	char nhanVienID[4];
	char tenNV[30];
	int tuoi, luong;
} NhanVien;
vector<NhanVien> dsNV;
char *fileName="nhanvien.dat";
//them NhanVien(nv) vao dsNV. Neu them thanh cong tra ve true, nguoc lai tra ve false
bool themNV(NhanVien nv);
void inNV(NhanVien nv);
void inDSNV();
// Nhap va tra ve 1 NhanVien tu ban phim
NhanVien nhapNVTuBP();
//Xoa mot NhanVien khoi danh sach
bool XoaNV(char* nvID);
// Cap nhat thong tin cua nvMoi vao mot NhanVien da co trong dsNV;
void capNhatNV(NhanVien nvMoi);
void docNVTuFile(char* fileName);
void ghiNVVaoFile(char* fileName);
int main()
{
	NhanVien nv1, nv2;
	strcpy(nv1.nhanVienID, "001");
	strcpy(nv1.tenNV, "Nguyen Van An");
	nv1.tuoi=30;
	nv1.luong= 300000;
	strcpy(nv2.nhanVienID, "002");
	strcpy(nv2.tenNV, "Nguyen Van Binh");
	nv2.tuoi=28;
	nv2.luong= 350000;
	themNV(nv1);
	themNV(nv2);
	themNV(nv2);
	inDSNV();
	//themNV(nhapNVTuBP());
//	cout<<"Danh sach nhan vien sau khi them:\n";
//	inDSNV();
	cout<<"Nhap thong tin Nhan vien can cap nhat:\n";
	NhanVien nvMoi = nhapNVTuBP();
	capNhatNV(nvMoi);
	cout<<"Danh sach nhan vien sau khi cap nhat:\n";
	inDSNV();
}

bool themNV(NhanVien nv)
{
	int size= dsNV.size();
	for(int i=0; i<size; i++)
		if(strcmp(nv.nhanVienID, dsNV[i].nhanVienID)==0)
			return false;
	dsNV.push_back(nv);
	ghiNVVaoFile(fileName);
	return true;
}

void inNV(NhanVien nv)
{
	cout<<"Ma NV: "<<nv.nhanVienID<<"\n";
	cout<<"Ten NV: "<<nv.tenNV<<"\n";
	cout<<"Tuoi: "<<nv.tuoi<<"\n";
	cout<<"Luong: "<<nv.luong<<"\n";
	cout<<"------------------------\n";
}
void inDSNV()
{
	int size= dsNV.size();
	for(int i=0; i<size; i++)
		inNV(dsNV[i]);
}
 
NhanVien nhapNVTuBP()
{
	NhanVien nv;
	cout<<"Nhap ma NV:"; fflush(stdin);
	gets(nv.nhanVienID);
	cout<<"Nhap ten NV:"; fflush(stdin);
	gets(nv.tenNV);
	cout<<"Nhap tuoi NV:";
	cin>>nv.tuoi;
	cout<<"Nhap luong NV:";
	cin>>nv.luong;
	return nv;
}
bool XoaNV(char* nvID)
{
	int size= dsNV.size();
	int vtXoa=-1;
	for(int i=0; i<size; i++)
		if(strcmp(nvID, dsNV[i].nhanVienID)==0)
		{
			vtXoa=i;
			break;
		}
	if(vtXoa!=-1)
	{
		dsNV.erase(dsNV.begin()+vtXoa);
		ghiNVVaoFile(fileName);
		return true;
	}
	return false;
}

void capNhatNV(NhanVien nvMoi)
{
	int size= dsNV.size();
	int vtCapNhat=-1;
	for(int i=0; i<size; i++)
		if(strcmp(nvMoi.nhanVienID, dsNV[i].nhanVienID)==0)
		{
			vtCapNhat=i;
			break;
		}
	if(vtCapNhat!=-1)
	{
		strcpy(dsNV[vtCapNhat].nhanVienID, nvMoi.nhanVienID);
		strcpy(dsNV[vtCapNhat].tenNV, nvMoi.tenNV);	
		dsNV[vtCapNhat].tuoi=nvMoi.tuoi;
		dsNV[vtCapNhat].luong=nvMoi.luong;
		ghiNVVaoFile(fileName);
	}
}

void docNVTuFile(char* fileName)
{
	dsNV.clear();
	FILE *f;
	f= fopen(fileName, "rb");
	if(f!=NULL)
	{
		while(!feof(f))
		{
			NhanVien nv;
			fread(&nv, sizeof(NhanVien), 1, f);
			dsNV.push_back(nv);
		}
		fclose(f);
		dsNV.pop_back();
	}	
}

void ghiNVVaoFile(char* fileName)
{
	int size = dsNV.size();
	FILE *f;
	f= fopen(fileName, "wb");
	NhanVien nv;
	for(int i=0; i<size; i++)
	{
		nv= dsNV[i];
		fwrite(&nv, sizeof(NhanVien), 1, f);
	}
	
	fclose(f);
}
