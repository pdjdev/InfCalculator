#include <stdio.h>
#include "link.h"
#include "calc.h"
#include "task.h"

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
