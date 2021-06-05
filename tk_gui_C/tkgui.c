#include <stdio.h>
#include <string.h>
#include "tk.h"
#include "tcl.h"
#define TK_SILENCE_DEPRECATION 1

char *labelvar = "label_var";
char *invar = "entry_var";
char *suffvar = "format_var";
char *gasvar = "gas_var";

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
    char label_buffer[80];
    char format[] = "%.1f";

    if (Tcl_GetVar(interp, suffvar, 4) == NULL){
        printf("Error: Tcl_GetVar %s", Tcl_GetStringResult(interp));
    }else
    {
        if (strlen(Tcl_GetVar(interp, suffvar, 4)) > 0){
            format[2] = *(char *) Tcl_GetVar(interp, suffvar, 4);
        }
        printf("GAS = %s", (char *) Tcl_GetVar(interp, gasvar, 4));
    };
    
    // pass arguments in Tcl script through argv variable
    for (i=0; i<argc; i++){
        if (Tcl_GetDouble(interp, argv[i], &value) == TCL_OK){
            Tcl_GetDouble(interp, Tcl_GetVar(interp, invar, 0), &entry);
            sprintf(label_buffer, format, add(value, entry));
            Tcl_SetVar(interp, labelvar, label_buffer, 0);
        };
    }

    Tcl_GetDouble(interp, Tcl_GetVar(interp, invar, 4), &value);

    sprintf(label_buffer, format, add(value, value));
    Tcl_SetVar(interp, labelvar, label_buffer, 0);

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

    sprintf(version, "Tcl/Tk %d.%d.%d\n", major, minor, patch);

    // Run sequentially the Tk commands for creating the GUI
    char *pchFile = 
    "wm title . \"version\"\n"
    "wm geometry . 800x300\n"
    "frame .fr\n"
    "pack .fr -fill both -expand TRUE\n"
    "grid columnconfigure .fr 0 -weight 1\n"
    "grid columnconfigure .fr 1 -weight 1\n"
    "grid rowconfigure .fr 0 -weight 1\n"
    "grid rowconfigure .fr 1 -weight 1\n"
    "grid rowconfigure .fr 2 -weight 1\n"
    "button .fr.but -text \"test\" -command \"func\"\n"
    "grid .fr.but -row 0 -column 0 -columnspan 2 -sticky nswe\n"
    "label .fr.value -text \"LABEL\" -textvariable label_var\n"
    "grid .fr.value -row 1 -column 0 -columnspan 2 -sticky nswe\n"
    "entry .fr.in -textvariable entry_var\n"
    "grid .fr.in -row 2\n"
    "bind .fr.in <Return> \"func\"\n"
    "ttk::entry .fr.suff -textvariable format_var\n"
    "grid .fr.suff -row 2 -column 1\n"
    "set format_var 0\n"
    "ttk::combobox .fr.combo -values { \"O2\" \"N2\"} -textvariable gas_var\n"
    "grid .fr.combo -row 3 -column 0 -columnspan 2 -sticky nsew\n"
    "set gas_var \"O2\"";

    // link the interfacing function to Tcl interpreter
    Tcl_CreateCommand(interp, "func", func, NULL, NULL);

    // Start GUI and check if any errors
    if (Tcl_Eval(interp, pchFile) == TCL_OK){
        printf("Tcl_Eval main OK %s\n", Tcl_GetStringResult(interp));
        Tk_MainLoop();
    }
    else{
        printf("Tcl_Eval NOK %s\n", Tcl_GetStringResult(interp));
    };
}
