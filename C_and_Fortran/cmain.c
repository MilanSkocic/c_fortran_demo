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
 * @param[in] string C string
 * @param[in] length Length of the string
 */
extern void f_print(char *string, int length);

/**
 * @brief C program
 * 
 * @return int 
 */
int main(){

    char string[] = "Send a C string to a Fortran function which print it.";
    f_print(string, strlen(string));
}
