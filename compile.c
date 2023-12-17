#include<stdio.h>
#include<stdlib.h>
int main()
{
    printf("Compiler: g++\n");
    printf("Compiling *.cpp -> .o\n");
    system("g++ -c *.cpp");
    printf("Linking .o files to executable XLGD\n");
    system("g++ *.o -o XLGD");
    return 0;
}