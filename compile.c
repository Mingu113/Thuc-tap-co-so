// Use C because other was written in C++ and I don't want for this one to be compiled too
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
void open()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    LPSTR XLGD = "XLGD";
    // Start the child process.
    if (!CreateProcess(NULL,    // No module name (use command line)
                       XLGD, // Command line
                       NULL,    // Process handle not inheritable
                       NULL,    // Thread handle not inheritable
                       FALSE,   // Set handle inheritance to FALSE
                       0,       // No creation flags
                       NULL,    // Use parent's environment block
                       NULL,    // Use parent's starting directory
                       &si,     // Pointer to STARTUPINFO structure
                       &pi)     // Pointer to PROCESS_INFORMATION structure
    )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles.
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
int main(int argc, char *argv[])
{
    printf("Compiler: g++\n");
    printf("Compiling *.cpp -> .o: ");
    char command1[] = "g++ -fopenmp -lgomp -Ofast -flto -c *.cpp";
    puts(command1);
    if (system(command1) == 0)
    {
        char command2[] = "g++ -fopenmp -lgomp -Ofast -flto *.o -o XLGD";
        printf("Linking .o files into executable XLGD: ");
        puts(command2);
        if (system(command2) == 0)
        {
            if (strcmp(argv[1], "y") == 0)
            {
                printf("Executing executable");
                open();
            }
        }
    }
    return 1;
}