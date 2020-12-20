LINK plus(LINK a, LINK b) { //LINK a와 LINK b를 인자로 받아 결과를 LINK형 자료로 반환하는 함수

    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    bool positive;
    unsigned long long point_count = 0;
    char now = 0;
    char up = 0;

    if(compare(a,b) == 2) { //연결리스트 a와 b의 절댓값을 비교해 b의 절댓값이 크다면, a와 b를 스왑한다.
        LINK tmp = a;
        a = b;
        b = tmp;
    }

    positive = (a->d == '+');   //a의 부호가 '+'인지 '-'인지 판단한다.

    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b); //a와 b의 부호를 뗀 숫자값만을 num1과 num2로 가리킨다.
    
    num2 = Upzero_fill(num1,num2);  //num1과 num2의 소수점 위 자릿수를 동일하게 맞춰준다.

    a = num1; num1 = char_to_list('0'); concatenate(num1, a);
    a = num2; num2 = char_to_list('0'); concatenate(num2, a);   //num1과 num2 합 계산 후 받아올림이 남아있을 경우, 이를 위한 노드를 추가한다. e.g) 500+500

    Downzero_fill(num1,num2);   //num1과 num2의 소수점 아래 자릿수를 동일하게 맞춰준다.
 
    a = last_link(num1);
    b = last_link(num2);    //a, b가 num1의 num2의 마지막 노드를 가리키게 한다.

    while(a!=NULL){ //a가 NULL 아닐 동안 아래를 반복한다 : 각 자리의 노드를 더해 a에 저장한다.

        if(a->d == '.') {
            a = a->prev;
            b = b->prev;
            continue;
        }

        char number1 = a->d-'0';
        char number2 = b->d-'0';

        now = number1 + number2 + up;
        
        up = now/10;    //받아올림수가 있는지 확인한다.
        a->d = now%10 + '0';
        a = a->prev;
        b = b->prev;
    }
    
    ans = copy_link(num1);  //a가 가리키던 num1의 연결리스트를 복사하여, ans로 가리킨다. 즉, 더한 결과값을 ans가 가리킨다.

    free_all(num1); free_all(num2);

    zero_erase(ans);    //소수점 아래의 필요없는 0을 지운다.


    a = ans;
    ans = char_to_list(positive ? '+' : '-');
    concatenate(ans,a);

    a = ans->next;
    while(a->next->d != '.' && a->d == '0') { del_link(ans->next); a=a->next; }

    return ans; //결과값 ans를 리턴한다.
}


LINK minus(LINK a, LINK b) {    //LINK a와 LINK b를 인자로 받아  결과를 LINK형 자료로 반환하는 함수.

    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    bool positive;
    char big_num;
    unsigned long long int point_count = 0; 
    char now = 0;
    char down = 0;

    big_num = compare(a,b);

    if(big_num == 3){ // 둘의 절대값이 같을 때 둘을 빼면 0이 되므로 결과 반환
        ans = char_to_list('+');
        insert(ans,'.');
        insert(ans,'0');
        free_all(a); free_all(b);
        return ans;
    }
    
    if(big_num == 2) { //연결리스트 a와 b의 절댓값을 비교해 b의 절댓값이 크다면, a와 b를 스왑한다.
        num_copy = a;
        a = b;
        b = num_copy;
    }

    positive = (a->d == '+');   //a의 부호가 '+'인지 '-'인지 판단한다.

    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);
    
    num2 = Upzero_fill(num1,num2);

    Downzero_fill(num1,num2);   //num1과 num2의 소수점 아래 자릿수를 동일하게 맞춰준다.

    a = last_link(num1);
    b = num2;
    for(; a->d != '.'; a=a->prev) point_count++; del_link(a);
    for(; b->d != '.'; b=b->next); del_link(b); //소수점이 있는 자리를 카운트하고 소수점을 삭제한다.

    a = last_link(num1);
    b = last_link(num2);

    while(a!=NULL) {    //a가 NULL 아닐 동안 아래를 반복한다 : 각 자리의 노드를 빼 a에 저장한다.
        char number1 = a->d-'0';
        char number2 = b->d-'0';
        char check = 0;
        if(number2-down > number1) {number1 += 10; check = 1;};
        now = number1 - number2 + down;
        down = check ? -1 : 0;  //받아내림수가 있는지 확인한다.
        a->d = now + '0';
        a = a->prev;
        b = b->prev;
    }
    
    ans = copy_link(num1);  //a가 가리키던 num1의 연결리스트를 복사하여, ans로 가리킨다. 즉, 더한 결과값을 ans가 가리킨다.
    free_all(num1); free_all(num2);

    a = last_link(ans);
    while(point_count--) a = a->prev;
    insert(a,'.');  //결과값에 소수점을 다시 붙여준다.
    
    zero_erase(ans);    //소수점 아래의 필요없는 0을 지운다.
    
    a = ans;
    ans = char_to_list(positive ? '+' : '-');
    concatenate(ans,a); //결과값에 부호를 다시 붙여준다.

    a = ans->next;
    for(; a->next->d != '.' && a->d == '0'; a=a->next) del_link(ans->next);

    return ans; //결과값 ans를 리턴한다.
}


LINK multiple(LINK num1, LINK num2) {   //LINK a와 LINK b를 인자로 받아 곱한 결과를 LINK형 자료로 반환하는 함수

    LINK ans; 
    LINK num_copy;
    LINK num1_last = last_link(num1);
    LINK num2_last = last_link(num2);
    LINK t1 = copy_link(num1);
    LINK t2 = copy_link(num2);
    LINK num1_int = copy_link(num1->next);
    LINK num2_int = copy_link(num2->next);
    LINK mul1;
    LINK mul2;
    LINK input;
    LINK zero_link;
    LINK save;
    bool positive;

    positive = (num1->d == num2->d);    //num1, num2의 부호가 같은지 확인한다. 같다면 T, 다르면 F.
 
    unsigned long long point = 0;
    num_copy = num1_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3 
    num_copy = num2_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3+4=7  //num1, num2의 소수점 아래 자릿수를 카운트한다.

    num_copy = num1_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);
    num_copy = num2_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);  //num1, num2의 소수점을 삭제한다.

    mul1 = last_link(num1_int);
    unsigned long long int zero = 0;
    for(; mul1 != NULL; mul1 = mul1->prev) {    //mul1이 NULL이 아닐 때동안 아래를 반복한다. : 각 자리 노드를 곱하고, 그 값을 전의 결과값과 더한다.
        mul2 = last_link(num2_int);
        char now = (mul1->d-'0') * (mul2->d-'0'); 
        char up = now/10;   //받아올림수가 있는지 확인
        now %=10;

        input = char_to_list(now + '0');

        num_copy = input;
        mul2 = mul2->prev;

        for(; mul2 != NULL; mul2 = mul2->prev) {    //mul2가 NULL이 아닐때 동안 아래를 반복한다. : mul2 연결리스트 수식과 mul1의 노드를 곱하는 연산을 한다.
            if(mul2->d == '.') {continue;}
            now = (mul1->d-'0') * (mul2->d-'0') + up;
            up = now/10;
            now %= 10;
            insert(num_copy, now + '0');
            num_copy = num_copy->next;
        }

        if(up != 0) { insert(num_copy, up+'0'); }   //받아올림수가 존재하면 옆에 붙여준다.
        num_copy = last_link(input);
        for( ; num_copy->prev != NULL; num_copy = num_copy->prev) {
            if(num_copy->d != '0') break;
        }
        
        if(zero>0){ //zero가 0 보다 크면 아래 조건문을 수행한다.
            zero_link = char_to_list('0');
            for(unsigned long long i=1; i<zero; i++) {
                insert(zero_link,'0');
            }
            concatenate(zero_link,input);
            input = zero_link;  //zero만큼의 '0' 노드의 개수를 가진 연결리스트를 붙인다.
        } 
        
        num_copy = last_link(input);
        while(1) {  //계산 후 남은 '0'을 지운다.
            if(num_copy->prev == NULL || num_copy->d != '0') break;
            LINK save = num_copy->prev;
            del_link(num_copy);
            num_copy = save;
        }

        if(!zero) ans = copy_link(input);   //zero가 0이면 input의 연결리스트를 복사하여, ans로 가리킨다
        
        else {  //zero가 0이 아닐 때 아래를 수행한다. : 곱하여 나온 값을 전에 나온 값과 
            unsigned long long alen = count(ans);
            unsigned long long blen = count(input);

            if(blen>alen){
                num_copy = ans;
                ans = input;
                input = num_copy;
            }
            save = ans;
            num_copy = input;
            now = 0;
            up = 0;
            for(; num_copy != NULL; num_copy = num_copy->next) {
                now = num_copy->d-'0' + save->d-'0' +up;
                up = now/10;
                now = now%10;
                save->d = now+'0';
                save = save->next;
            }
            for(; up && save != NULL; save = save->next) {
                now = save->d-'0' + up;
                up = now/10;
                now = now%10;
                save->d = now+'0';
            }
            if(up) {
                save = last_link(ans);
                insert(save,'1');
            }
        }
        free_all(input);
        zero++; 
    }
    
    unsigned long long anslen = count(ans);
    if(anslen > point) {    //결과값의 길이가 point 크기보다 더 클 때 (e.g 12.345)
        num_copy = ans;
        save = ans;
        if(positive) ans = char_to_list('+');
        else ans = char_to_list('-');

        for(; num_copy!=NULL; num_copy = num_copy->next) { insert(ans,num_copy->d); }
        free_all(save);
        
        LINK t3 = last_link(ans);
        LINK tl1 = last_link(t1);
        LINK tl2 = last_link(t2);

        while(tl1 != NULL && tl1->d != '.'){
            t3 = t3->prev;
            tl1 = tl1->prev;
        }
        while(tl2 != NULL && tl2->d != '.'){
            t3 = t3->prev;
            tl2 = tl2->prev;
        }

        insert(t3, '.');
        
    } else {    //결과값의 길이가 point 크기보다 작을 때 (e.g 0.001)
        num_copy = ans;
        save = ans;
        
        ans = char_to_list('0');
        for(; num_copy!=NULL; num_copy = num_copy->next) { insert(ans,num_copy->d); }
        free_all(save);
        num_copy = ans->next;
        num_copy->prev = NULL;
        ans->next = NULL;
        ans = num_copy;

        LINK t3 = last_link(ans);
        LINK tl1 = last_link(t1);
        LINK tl2 = last_link(t2);

        while(tl1 != NULL && tl1->d != '.'){
            if(t3->prev == NULL){
                LINK z = char_to_list('0');
                z->next = t3;
                t3->prev = z;
                t3 = z;
            }
            else t3 = t3->prev;
            tl1 = tl1->prev;
        }
        while(tl2 != NULL && tl2->d != '.'){
            if(t3->prev == NULL){
                LINK z = char_to_list('0');
                z->next = t3;
                t3->prev = z;
                t3 = z;
            }
            else t3 = t3->prev;
            tl2 = tl2->prev;
        }
        insert(t3, '.');

        LINK sign;
        if(positive) {sign = char_to_list('+'); concatenate(sign, t3); ans = sign;}
        else {sign = char_to_list('-'); concatenate(sign, t3); ans = sign;}
    }
    zero_erase(ans);
    free_all(num1);     free_all(num2);
    free_all(num1_int); free_all(num2_int);
    return ans;
}

LINK calculator(LINK p1, LINK p2, char oper) {
    LINK p3;
    extern bool printlog;

    if((oper == '+' || oper=='-' || oper == '*') && printlog) {
        extern int calccount;
        printf("%d\t", ++calccount);
        print_link(p1); printf("\t\t");
        print_link(p2); printf("\t\t%c\n", oper);
    }

    if(oper == '+' || oper=='-') {
        if(oper == '-') { p2->d = (p2->d == '-' ? '+' : '-'); }
        if(p1->d + p2->d == '+'+'+' || p1->d + p2->d == '-'+'-') { p3 = plus(p1,p2); }
        else { p3 = minus(p1,p2); }
    }

    if(oper == '*') p3 = multiple(p1,p2);
    return p3;
}

