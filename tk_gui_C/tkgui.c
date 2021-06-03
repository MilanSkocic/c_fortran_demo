#include <stdio.h>
#include <string.h>
#include "tk.h"
#include "tcl.h"
#define TK_SILENCE_DEPRECATION 1

char *labelvar = "labelstr";
char *invar = "invar";
char *suffvar = "suffvar";
char *gasvar = "gasvar";

// C function implementations
double add(double a, double b){
    return a+b;
}

// Tcl vars must be converted to C types using the Tcl C API
int func(ClientData data, Tcl_Interp *interp, int argc, const char **argv){
    int i;
    double value=0.0;
    double entry=0.0;
    int suff = 0;
    char str[80];
    char format[4] = "%.1f";

    if (Tcl_GetVar(interp, suffvar, 4) == NULL){
        printf("Error in GetVar: %s", Tcl_GetStringResult(interp));
    }else
    {
        if (strlen(Tcl_GetVar(interp, suffvar, 4)) > 0){
            format[2] = *(char *) Tcl_GetVar(interp, suffvar, 4);
        }
        printf("GAS = %s", (char *) Tcl_GetVar(interp, gasvar, 4));
    };

    for (i=0; i<argc; i++){
        if (Tcl_GetDouble(interp, argv[i],&value) == TCL_OK){
            Tcl_GetDouble(interp, Tcl_GetVar(interp, invar, 0),&entry);
            printf("argv[%d] = %s %f\n", i, argv[i], value);
            sprintf(str, format, add(value, entry));
            Tcl_SetVar(interp, labelvar, str, 0);
        };
    }
    return TCL_OK;
}



int main(int argc, char **argv){

    char version[128];

    // prototype for the initialization function
    Tcl_Interp *interp = Tcl_CreateInterp();

    // Initialize Tcl and Tk
    Tcl_Init(interp);
    Tk_Init(interp);

    int major, minor, patch;
    Tcl_GetVersion(&major, &minor, &patch, NULL);

    sprintf(version, "Version %d.%d.%d\n", major, minor, patch);

    // Run sequentially the Tk commands for creating the GUI
    char *pchFile = "wm title . \"%s\"\n"
    "wm geometry . 600x300\n"
    "button .but -text \"test\" -command \"func 10 40\"\n"
    "grid .but -row 0\n"
    "label .value -text \"LABEL\" -textvariable %s\n"
    "grid .value -row 1\n"
    "entry .in -textvariable %s\n"
    "grid .in -row 2\n"
    "entry .suff -textvariable %s\n"
    "grid .suff -row 2 -column 1\n"
    "set %s 0\n"
    "ttk::combobox .combo -values { \"O2\" \"N2\"} -textvariable %s\n"
    "grid .combo -row 3 -column 1\n"
    "set %s \"O2\"";

    // replace var names
    char msg[1024];
    sprintf(msg, pchFile, version, labelvar, invar, suffvar, suffvar, gasvar, gasvar);

    // link the interfacing function to Tcl interpreter
    Tcl_CreateCommand(interp, "func", func, NULL, NULL);

    // Start GUI and check if any errors
    if (Tcl_Eval(interp, msg) == TCL_OK){
        printf("Tcl_Eval main OK %s\n", Tcl_GetStringResult(interp));
        Tk_MainLoop();
    }
    else{
        printf("Tcl_Eval NOK %s\n", Tcl_GetStringResult(interp));
    };
}
