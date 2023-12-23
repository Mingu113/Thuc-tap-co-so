// Use C because other was written in C++ and I don't want for this one to be compiled too
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    printf("Compiler: g++\n");
    printf("Compiling *.cpp -> .o: ");
    char command1[] = "g++ -fopenmp -lgomp -c *.cpp -O3";
    puts(command1);
    if (system(command1) == 0)
    {
        char command2[] = "g++ -fopenmp -lgomp *.o -O3 -o XLGD";
        printf("Linking .o files into executable XLGD: ");
        puts(command2);
        if (system(command2) == 0)
        {
            if (strcmp(argv[1], "y") == 0)
            {
                printf("Executing executable");
                system("XLGD");
            }
        }
    }
    return 1;
}