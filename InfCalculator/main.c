#include <stdio.h>
#include "link.c"
#include "calc.c"
#include "task.c"

int main(int argc, char* argv[]) {

    // checking arguments
    if (argc != 2){
        fprintf(stderr ,"\n%s%s%s\n%s\n\n",
        "Usage: ", argv[0], " input",
        "Enter the location of text file that contains a math expression.");       
        exit(2);
    }
    
    return 0;
}
