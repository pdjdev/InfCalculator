#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "link.c"
#include "stack.c"
#include "calc.c"
#include "task.c"

#define INPUT_SIZE 65535

bool printlog = false;   // log 출력 여부
int calccount = 0;      // log - 계산 횟수

int main(int argc, char* argv[]) {

    // argument check
    if (argc == 1 || argc > 3){
        fprintf(stderr ,"\n%s%s%s\n%s%s%s\n%s%s%s\n%s%s%s\n%s\n%s\n\n%s\n\n",
        "Usage:\t", argv[0], " input",
        "\t", argv[0], " input -log",
        "\t", argv[0], " -type",
        "\t", argv[0], " -type -log",
        "Enter the location of text file that contains a math expression.",
        "(Or you can type directly with -type option)",
        "Caution: Enabling the -log option may slow down the process.");       
        exit(2);
    }

    char inputargc = 1;

    for(int i=1; i<argc; i++) {
        if (!strcmp(argv[i], "-type") || !strcmp(argv[i], "--type")) {
            inputargc = 0;
        }

        if (!strcmp(argv[i], "-log") || !strcmp(argv[i], "--log")) {
            printlog = true;
            // 인풋이 type가 아닌 경우
            if (inputargc != 0) {
                if (i==1) inputargc = 2;
            }
        }      
    }

    LINK exp_head;

    if (inputargc != 0) {
        exp_head = GetExpr(argv[inputargc]);
    } else {
        char input[INPUT_SIZE];
        printf("Enter an expression: ");
        scanf("%[^\n]s", input);
        exp_head = StringToLink(input);
    }
    
    exp_head = DelSpace(exp_head);

    //에러가 체크되어 있으면 오류문구 출력 후 종료
    char errorcheck = ErrChk(exp_head);    
    if(errorcheck) {
        //오류 발생
        printf("An error has occured: ");    
        printf(ErrMsg(errorcheck));
        printf(" (code %d)\n", errorcheck);
        free_all(exp_head);
        exit(1);
    }

    exp_head = FixExpr(exp_head);
    if (printlog) { printf("Fixed Expression:\n"); print_link(exp_head); printf("\n\n"); }
    exp_head = PostFix(exp_head);
    if (printlog) { printf("Postfix:\n"); print_link(exp_head); printf("\n\n"); }

    printf("Calculating...\n");
    if (printlog) printf("#\tOperand\t\tOperand\t\tOperator\n");
    LINK answer = GetAnswer(exp_head);
    printf("...Complete!\n\n");
   
    //답 출력
    printf("Result : ");
    print_link(answer);
    printf("\n");

    free_all(answer);
    free_all(exp_head);
}
