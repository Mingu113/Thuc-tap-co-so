// Use C because other was written in C++ and I don't want for this one to be compiled too
#include <stdio.h>
#include <stdlib.h>
int main()
{
    printf("Compiler: g++\n");
    printf("Compiling *.cpp -> .o: ");
    char command1[] = "g++ -c *.cpp";
    puts(command1);
    if (system(command1) == 0)
    {
        char command2[] = "g++ *.o -o XLGD";
        printf("Linking .o files into executable XLGD: ");
        puts(command2);
        if (system(command2) == 0)
        {
            printf("Execute the program? (y/n): ");
            char choice;
            fflush(stdin);
            scanf("%c", &choice);
            if (choice == 'y')
                system("XLGD");
            return 0;
        }
        // if fail to execute command system, exit if
    }
    // if fail to execute command, exit if
    printf("Fail to execute command, check console, maybe it will display something\n");
    return 0;
}