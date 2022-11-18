#include <stdio.h>
#include <string.h>

extern void f_print(char *string, int length);

int main(){

    char string[] = "Send a C string to a Fortran function which print it.";
    f_print(string, strlen(string));
}
