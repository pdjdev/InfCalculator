// filename으로부터 문자열 읽어서 LIST로 변환
LINK GetExpr(char *filename) {
    FILE *fq = fopen(filename, "r"); 
    if(fq == NULL){
        printf("Error: Input file not found.\n");
        exit(0);
    }

    char input = getc(fq);

    if(input==EOF) {
        printf("Error: Input file is empty.\n");
        exit(0);
    }

    LINK exp_head = char_to_list(input);
    LINK exp = exp_head;
    
    //두번째 글자부터 입력 및 링크드리스트 넣기
    while(input = getc(fq)) {
        // 개행문자 or end of file
        if(input == EOF) break;
        LINK p = char_to_list(input);
        exp->next = p;
        p->prev = exp;
        exp = p;
    }
    fclose(fq);
    return exp_head;
}

// string의 문자열을 LIST로 변환
LINK StringToLink(char* string) {
    LINK exp_head = char_to_list(string[0]);
    LINK exp = exp_head;
    unsigned long long length = 1;

    while(length < strlen(string)) {
        LINK p = char_to_list(string[length]);
        exp->next = p;
        p->prev = exp;
        exp = p;
        length++;
    }
    
    return exp_head;
}

// 공백 제거 ('1   + 2' -> '1+2')
LINK DelSpace(LINK exp_head) {
    LINK exp = exp_head;
    LINK exp_x;
    while(exp->next != NULL) {
        if(exp->d != ' ' && exp->d != '\n') break;
        exp_x = exp->next;
        exp->next->prev = NULL;
        free(exp);
        exp = exp_x;
    }
    exp_head = exp;
    
    //식 중간중간에 있는 공백 제거
    exp = exp_head->next;
    while(exp!=NULL){
        if(exp->d == ' ' || exp->d == '\n'){
            exp_x = exp->prev;
            del_link(exp);
            exp = exp_x;
        }
        exp = exp->next;
    }
    return exp_head;
} 

// 오류 체크
char ErrChk(LINK exp_head) {
    char errorcheck = 0;
    LINK exp = exp_head;

    //중간부분 체크에 쓰일 변수 선언
    bool number = false; // 숫자가 있으면 true
    bool haspoint = false; // 소수점 있으면 true
    unsigned long long left_bracket = 0; // 왼괄호
    unsigned long long right_bracket = 0; // 우괄

    // 맨 앞에 나오면 안되는 게 있으면 에러 체크
    if(!(exp->d == '(' || exp->d == '-' || (exp->d >= '0' && exp->d <= '9'))) errorcheck = -1;

    //맨 앞이 숫자이면 숫자 나왔다고 알려주기
    if(exp->d>='0' && exp->d <='9') number = true;

    //중간부분
    exp = exp_head;
    while(exp->next != NULL){

        //에러가 체크되어 있으면 break
        if(errorcheck < 0) break;
        
        //숫자 하나에 .이 2개이면 에러 체크, 숫자 나왔는지 확인
        if((exp->d >= '0' && exp->d <= '9') || exp->d == '.'){
            number = true;
            if(!haspoint && exp->d == '.') haspoint = true;
            else if(haspoint && exp->d == '.') {errorcheck = -2; break;}
        }
        else haspoint = false;
        
        //괄호 개수 세기
        if(exp->d == '(') left_bracket ++;
        if(exp->d == ')') right_bracket ++;

        //우괄호가 더 많으면 에러체크
        if(left_bracket < right_bracket) {errorcheck = -3; break;}
        
        //나오면 안되는 문자
        if(!(exp->d == '+' || exp->d == '-' || exp->d == '*' || 
                    exp->d == '(' || exp->d == ')' || exp->d == '.' ||  (exp->d>='0'&&exp->d<='9'))){errorcheck = -4; break;}
        
        //연산자 다음에 나오면 안되는 문자
        if(exp->d == '+' || exp->d == '*' || exp->d == '-'){
            if(!(exp->next->d == '(' || (exp->next->d>='0' && exp->next->d<='9'))) {errorcheck = -5; break;}
        }

        if(exp->d == '('){
            if(!(exp->next->d == '('|| exp->next->d == '-' || 
                        (exp->next->d>='0' && exp->next->d<='9'))) {errorcheck = -6; break;}
        }
        /*if(exp->d == ')'){
            if(exp->next->d >= '0' && exp->next->d <='9') {errorcheck = -1; break;}
        }*/
        exp = exp->next;
    }

    // 아직까지 에러체크 안됐을때
    if (errorcheck>=0) {

        // 마지막 글자로 나오면 안되는게 나오면 에러체크 및 괄호 세기 및 숫자 체크
        if(exp->prev != NULL){
            if(!(exp->d == '+' || exp->d == '-' || exp->d == '*' || 
                        exp->d == '(' || exp->d == ')' || (exp->d>='0'&&exp->d<='9'))) errorcheck = -7;

            if(!(exp->d == ')' || (exp->d >= '0' && exp->d <= '9'))) errorcheck = -8;
            if(exp->d == ')') right_bracket++;
            if(exp->d >= '0' && exp->d<='9') number = true;
        }

        //숫자가 없으면 에러 체크
        if(!number) errorcheck = -9;

        //괄호 개수가 같지 않으면 에러 체크
        if(left_bracket != right_bracket) errorcheck = -10;

    }
    return errorcheck;
}

// 오류 메시지 반환
char* ErrMsg(char errorcode) {
    switch (errorcode)
    {
    case -1: // 맨 앞에 올바르지 않은 문자열이 있음
        return "Invalid character at the beginning of the input";
    
    case -2: // 피연산자 하나에 소수점이 두개 이상 발견됨
        return "More than one decimal point was found in an operand";
        
    case -3: // 우괄호가 더 많음
        return "Right bracket outnumbers the left bracket in the expression";

    case -4: // 올바르지 않은 문자가 포함되어 있음
        return "Invalid character(s) in the expression (Only '+','-','*','(',')','.','0-9' are allowed)";

    case -5: // 연산자 다음에 올바르지 않은 문자가 포함되어 있음
        return "Invalid character(s) next to the operator (Only '(','0-9' are allowed)";

    case -6: // 좌괄호 다음에 올바르지 않은 문자가 포함되어 있음
        return "Invalid character(s) next to the left bracket (Only '(','-', '0-9' are allowed)";

    case -7: // 올바르지 않은 문자가 포함되어 있음
        return "Invalid character(s) in the expression (Only '+','-','*','(',')','.','0-9' are allowed)";
    
    case -8: // 식 끝에 올바르지 않은 문자가 포함되어 있음
        return "Invalid character(s) at the end of the input (Only ')','0-9' are allowed)";
    
    case -9: // 피연산자 없음
        return "No operand found";

    case -10: // 괄호 수가 맞지 않음
        return "Number of brackets mismatch";

    default:
        return "Unknown error";

    }
}

// 표현식을 프로그램이 해석할 수 있도록 수정
// ('-5+23(10)4' -> '0.-5.+23.*(10.)*4.')
LINK FixExpr(LINK exp_head) {
    LINK exp;
    // 맨 앞에 -가 나오는 경우, 맨 앞에 0 붙여주기   ( -   >   0- )
    if(exp_head->next != NULL && exp_head->d == '-'){
        LINK zero = char_to_list('0');
        concatenate(zero, exp_head);
        exp_head = zero;
    }

    // 중간 수정 파트 //
    exp = exp_head;
    bool dcpt = false; //소수점
    for(; exp!=NULL; exp=exp->next) {

        //피연산자를 만났을 때
        if((exp->d >='0' && exp->d <='9') || exp->d == '.') {

            // 다음 링크의 글자가 '(' 일 때 * 추가   ex) 2(3-2)  ->  2*(3-2)
            if(exp->next != NULL && exp->next->d == '(') insert(exp,'*');

            // .을 만나면 만났다고 체크
            if(exp->d == '.') dcpt = true;

            //다음 링크의 글자가 피연산자가 아닐 때
            if(exp->next != NULL && (exp->next->d <'0' || exp->next->d >'9') && exp->next->d != '.') {

                // 소수점이 없었다면 소수점하고 소수점 체크 변수 0으로 초기화
                if(!dcpt){
                    insert(exp,'.');
                    exp=exp->next;
                }
                // 소수점이 있었다면 0으로 초기화
                else dcpt = false;
            }
        }

        // 우괄호를 만나고, 바로 다음이 좌괄호 또는 피연산자이면 * 추가
        if(exp->next != NULL && exp->d == ')') {
            if(exp->next->d == '(' || (exp->next->d >='0' && exp->next->d <='9')) { insert(exp,'*'); }
        }
        else if(exp->d == '(') { // 좌괄호이고, 다음 문자가 '-' 이면 0 추가
            if(exp->next!=NULL && exp->next->d == '-') { insert(exp,'0'); }
        }
    }

    // 마지막 피연산자에 .이 없었다면 . 추가
    LINK exp_last = last_link(exp_head);
    exp = exp_last;
    if(!dcpt && exp->d>='0' && exp->d<='9') { insert(exp,'.'); }

    return exp_head;
}

// 연산자 우선순위 리턴
char GetPriority(DATA d, bool inStack) {
    unsigned int priority = -1;
    switch(d){
        case '(' :
            if(inStack) priority = 3;
            else priority = 0;
            break;
        case '*' :
            priority = 1;
            break;
        case '+' :
        case '-' :
            priority = 2;
            break;
    }
    return priority;
}

// 두 값중 우선순위 높음여부 비교
bool isPrior(DATA d1, DATA d2) {
    return (GetPriority(d1, true) <= GetPriority(d2, false));
}

// 중위 -> 후위식 변환 후 dll로 리턴하는 함수
LINK PostFix(LINK exp_head) {
    
    // 연산자를 비교해줄 스택 생성
    Stack oper_stack;
    InitStack(&oper_stack);

    // 수식을 받아 사용.
    LINK exp = exp_head;
    
   // 후위표기식을 저장할 DLL 헤드 생성. !!수정 필요!!
    LINK post_head = char_to_list('e'); //초기 'e' 노드 생성.. (수정 필요)
    LINK post = post_head;

    for(; exp != NULL; exp = exp->next) {

        // (1) 0~9이거나 .이다. (후위수식에) 피연산자 추가
        if((exp->d == '.') || (exp->d >= '0' && exp->d <= '9')){
            //concatenate(post, char_to_list(exp->d));
            LINK p = char_to_list(exp->d);
            post->next = p;
            p->prev = post;
            post = p;
    
            // 다음 문자가 피연산자가 아닐 경우
            if(!(exp->next != NULL && ((exp->next->d == '.') || 
                (exp->next->d >= '0' && exp->next->d <= '9')))){
                LINK s = char_to_list(' ');
                post->next = s;
                s->prev = post;
                post = s;
            }

        }
        
        // (2) 연산자 - ')' 이다.
        else if(exp->d == ')') {
            while(Top(&oper_stack)->d != '('){  //스택에 있는 '('를 찾기 전까지
                LINK oper = Pop(&oper_stack);   //스택의 탑을 팝한다.
                
                // 팝한 데이터를 후위표기식 뒤에 붙여준다.    
                post->next = oper;
                oper->prev = post;
                post = oper;

                LINK s = char_to_list(' ');
                post->next = s;
                s->prev = post;
                post = s;


                //받아온 탑을 해체.
                //free_all(oper);
            }   //'('를 만나 while을 빠져나오면, '('은 그냥 버린다.
            //스택의 탑에 위치한 '('를 팝해주고
            //노드를 삭제.
            free(Pop(&oper_stack));
        }


        // (3) 연산자 - ')' 제외 모든 연산자.
        else {
            // Stack 안의 탑 연산자와 우선순위 비교.
            // 넣을 연산자가 top보다 우선순위 높으면 그냥 스택에 넣음.
            // 낮으면 계속 pop해서 높을 때까지 맞춤.
            while(!IsEmpty(&oper_stack) && isPrior(Top(&oper_stack)->d,exp->d)) {
                LINK oper = Pop(&oper_stack);   //스택의 탑을 팝한다.
                
                // 팝한 데이터를 후위표기식 뒤에 붙여준다.
                post->next = oper;
                oper->prev = post;
                post = oper;

                LINK s = char_to_list(' ');
                post->next = s;
                s->prev = post;
                post = s;

                //받아온 탑을 해체.
                //free_all(oper);
            }   //다 끝나면 스택의 탑 연산자 우선순위가 낮게 됨.
            Push(&oper_stack, char_to_list(exp->d));
        }    
    }

    // 연산자 스택이 비어있지 않을 때 연산
    while(!IsEmpty(&oper_stack)){
        LINK oper = Pop(&oper_stack);   //스택의 탑을 팝한다.
                
        // 팝한 데이터를 후위표기식 뒤에 붙여준다.
        //concatenate(post, oper);
        post->next = oper;
        oper->prev = post;
        post = oper;

        
        //받아온 탑을 해체.
        //free_all(oper);
        LINK s = char_to_list(' ');
        post->next = s;
        s->prev = post;
        post = s;
    }
    
    //답 출력
    return post_head->next; //초기에 'e'를 넣엇음 -> next 주소를 반환해야함.
}

// 공백으로 분리된 후위표기식 LIST를 읽고 계산한 뒤 LIST로 리턴
LINK GetAnswer(LINK exp_head) {
    Stack exp_stack;
    InitStack(&exp_stack);
    //InitStack(&oper_stack);

    LINK expr = exp_head;
    LINK operand_head;
    LINK operand;

    bool adding_operand = false;

    while(expr != NULL) {

        //공백이 아닐 경우 (식 또는 숫자일 경우)
        if (expr->d != ' ') {            
            
            // 연산자일 경우
            if (expr->d == '+' || expr->d == '-' || expr->d == '*') {
                LINK p2 = Pop(&exp_stack); LINK p1 = Pop(&exp_stack);
                LINK p3 = calculator(p1, p2, expr->d);
                Push(&exp_stack, p3);

            } else { // 피연산자일 경우

                if (adding_operand == false) {

                    adding_operand = true;
                    // 표현식 내에서의 피연산자는 항상 양수이므로 +를 맨처음에 넣기
                    operand_head = char_to_list('+');
                    insert(operand_head, expr->d);
                    operand = operand_head->next;        

                } else {
                    insert(operand, expr->d);
                    operand = operand->next;
                }
            }           

        } else { // 드디어 공백을 만난 경우       
            // 띄어쓰기 직전 피연산자를 추가했었던 경우
            if (adding_operand) {
                adding_operand = false;
                Push(&exp_stack, operand_head);
            }       
        }

        // 리스트 넘기기
        expr = expr->next;
    }
    return Pop(&exp_stack);
}

