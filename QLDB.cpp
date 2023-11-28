#include<stdio.h>
#include<conio.h>
#include<vector>
#include<iostream>
#include<string.h>
using namespace std;
typedef struct
{
	char sdt[11];
	char ten[20];
} Contact;
char *fileName="danhba.dat";
vector<Contact> db;
void docDBTuFile();
void ghiDBVaoFile();
void themMoi(Contact c);
void xoaContact(char* sdt);
void suaContact(Contact contactMoi);
void inContact(Contact c);
void inDanhBa();
int main()
{
	cout<<"Hello"<<"\n";
	docDBTuFile();
	inDanhBa();
	Contact c1;
	strcpy(c1.sdt, "456");
	strcpy(c1.ten, "Thu Du");
	Contact c2;
	strcpy(c2.sdt, "654");
	strcpy(c2.ten, "Phuong Phuong");
	themMoi(c1);
	themMoi(c2);
	//docDBTuFile();
	cout<<"Danh ba moi:\n";
	inDanhBa();
}

void docDBTuFile()
{
	db.clear();
	FILE *f;
	f= fopen(fileName, "rb");
	if(f!=NULL)
	{
		while(!feof(f))
		{
			Contact c;
			fread(&c, sizeof(Contact), 1, f);
			db.push_back(c);
		}
		fclose(f);
		db.pop_back();
	}	
}

void ghiDBVaoFile()
{
	int size = db.size();
	FILE *f;
	f= fopen(fileName, "wb");
	Contact c;
	for(int i=0; i<size; i++)
	{
		c= db[i];
		fwrite(&c, sizeof(Contact), 1, f);
	}
	
	fclose(f);
}
void themMoi(Contact c)
{
	db.push_back(c);
	ghiDBVaoFile();
}

void inContact(Contact c)
{
	cout<<"So DT: "<<c.sdt<<"\n";
	cout<<"Ten: "<<c.ten<<"\n";
	cout<<"----------------------\n";
}

void inDanhBa()
{
	int size = db.size();
	for(int i =0 ;i<size;i++)
	{
		inContact(db[i]);
	}
}

void xoaContact(char* sdt)
{
	
}
