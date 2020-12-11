#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "link.c"
#include "stack.c"
#include "calc.c"
#include "task.c"

bool printlog = true;
int calccount = 0;

int main(int argc, char* argv[]) {

    // argument check
    if (argc == 1 || argc > 3){
        fprintf(stderr ,"\n%s%s%s\n%s%s%s\n%s\n\n",
        "Usage:\t", argv[0], " input",
        "\t", argv[0], " input -log",
        "Enter the location of text file that contains a math expression.");       
        exit(2);
    }

    char inputargv = 1;

    if (argc > 2) {
        if (!strcmp(argv[1], "-log") || !strcmp(argv[1], "--log")) inputargv = 2;
        else if (!strcmp(argv[2], "-log") || !strcmp(argv[2], "--log")) {}
        else { printlog = false; }
    } else { printlog = false; }

    LINK exp_head = GetExpr(argv[inputargv]);
    exp_head = DelSpace(exp_head);

    //에러가 체크되어 있으면 오류문구 출력 후 종료
    char errorcheck = ErrChk(exp_head);    
    if(errorcheck){
        //오류 발생
        printf("An error has occured: ");
        free_all(exp_head);
        exit(1);
    }

    exp_head = FixExpr(exp_head);
    if (printlog) printf("Fixed Expression:\n"); print_link(exp_head); printf("\n\n");
    exp_head = PostFix(exp_head);
    if (printlog) printf("PostFix:\n"); print_link(exp_head); printf("\n\n");

    printf("Calculating...\n");
    if (printlog) printf("#\tOperand\t\tOperand\t\tOperator\n");
    LINK answer = GetAnswer(exp_head);
    printf("...Complete!\n");
   
    //답 출력
    printf("Result : ");
    print_link(answer);
    printf("\n");

    free_all(answer);
    free_all(exp_head);
}
