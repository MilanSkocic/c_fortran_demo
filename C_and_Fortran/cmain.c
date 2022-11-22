/**
 * @file 
 * @author Milan Skocic
 * @brief Program which calls a Fortran function from C.
 * 
 */

#include <stdio.h>
#include <string.h>

/**
 * @brief Fortran subroutine which prints an C string.
 * 
 * @param string C string
 * @param length Length of the string
 */
extern void f_print(char *string, int length);

int main(){

    char string[] = "Send a C string to a Fortran function which print it.";
    f_print(string, strlen(string));
}
