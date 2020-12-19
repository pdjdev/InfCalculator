// 더하기
LINK plus(LINK a, LINK b) {

    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    bool positive;
    unsigned long long point_count = 0;
    char now = 0;
    char up = 0;

    if(compare(a,b) == 2) {
        LINK tmp = a;
        a = b;
        b = tmp;
    }

    positive = (a->d == '+');

    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);
    
    num2 = Upzero_fill(num1,num2);

    a = num1; num1 = char_to_list('0'); concatenate(num1, a);
    a = num2; num2 = char_to_list('0'); concatenate(num2, a);

    Downzero_fill(num1,num2);

    a = last_link(num1);
    b = num2;
    for(; a->d != '.'; a=a->prev) point_count++; del_link(a);
    for(; b->d != '.'; b=b->next); del_link(b);
 
    a = last_link(num1);
    b = last_link(num2);

    while(a!=NULL){
        char number1 = a->d-'0';
        char number2 = b->d-'0';

        now = number1 + number2 + up;
        
        up = now/10;
        a->d = now%10 + '0';
        a = a->prev;
        b = b->prev;
    }
    
    ans = copy_link(num1);

    free_all(num1); free_all(num2);

    a = last_link(ans);
    while(point_count--) a = a->prev;
    insert(a,'.');

    zero_erase(ans);

    a = ans;
    ans = char_to_list(positive ? '+' : '-');
    concatenate(ans,a);

    a = ans->next;
    while(a->next->d != '.' && a->d == '0') { del_link(ans->next); a=a->next; }

    return ans;
}

// 빼기
LINK minus(LINK a, LINK b) {

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

    if(big_num == 3){ // 둘의 절대값이 같을 때
        ans = char_to_list('+');
        insert(ans,'.');
        insert(ans,'0');
        free_all(a); free_all(b);
        return ans;
    }
    
    if(big_num == 2) { // b가 더 크면 b가 a로 이동
        num_copy = a;
        a = b;
        b = num_copy;
    }

    positive = (a->d == '+');

    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);
    
    num2 = Upzero_fill(num1,num2);

    Downzero_fill(num1,num2);

    a = last_link(num1);
    b = num2;
    for(; a->d != '.'; a=a->prev) point_count++; del_link(a);
    for(; b->d != '.'; b=b->next); del_link(b);

    a = last_link(num1);
    b = last_link(num2);

    while(a!=NULL) {
        char number1 = a->d-'0';
        char number2 = b->d-'0';
        char check = 0;
        if(number2-down > number1) {number1 += 10; check = 1;};
        now = number1 - number2 + down;
        down = check ? -1 : 0;
        a->d = now + '0';
        a = a->prev;
        b = b->prev;
    }
    
    ans = copy_link(num1);
    free_all(num1); free_all(num2);

    a = last_link(ans);
    while(point_count--) a = a->prev;
    insert(a,'.');
    
    zero_erase(ans);
    
    a = ans;
    ans = char_to_list(positive ? '+' : '-');
    concatenate(ans,a);

    a = ans->next;
    for(; a->next->d != '.' && a->d == '0'; a=a->next) del_link(ans->next);

    return ans;
}

// 곱하기
LINK multiple(LINK num1, LINK num2) {

    LINK ans; 
    LINK num_copy;
    LINK num1_last = last_link(num1);
    LINK num2_last = last_link(num2);
    LINK num1_int = copy_link(num1->next);
    LINK num2_int = copy_link(num2->next);
    LINK mul1;
    LINK mul2;
    LINK input;
    LINK zero_link;
    LINK save;
    bool positive;

    positive = (num1->d == num2->d);
 
    unsigned long long point = 0;
    num_copy = num1_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3 
    num_copy = num2_last;
    for( ; num_copy->d != '.' ; num_copy = num_copy->prev) point++;//3+4=7

    num_copy = num1_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);
    num_copy = num2_int;
    for( ; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);

    mul1 = last_link(num1_int);
    unsigned long long int zero = 0;
    for(; mul1 != NULL; mul1 = mul1->prev) {
        mul2 = last_link(num2_int);
        char now = (mul1->d-'0') * (mul2->d-'0'); 
        char up = now/10;
        now %=10;

        input = char_to_list(now + '0');

        num_copy = input;
        mul2 = mul2->prev;

        for(; mul2 != NULL; mul2 = mul2->prev) {
            now = (mul1->d-'0') * (mul2->d-'0') + up;
            up = now/10;
            now %= 10;
            insert(num_copy, now + '0');
            num_copy = num_copy->next;
        }

        if(up != 0) { insert(num_copy, up+'0'); }
        num_copy = last_link(input);
        for( ; num_copy->prev != NULL; num_copy = num_copy->prev) {
            if(num_copy->d != '0') break;
        }
        
        if(zero>0){
            zero_link = char_to_list('0');
            for(unsigned long long i=1; i<zero; i++) {
                insert(zero_link,'0');
            }
            concatenate(zero_link,input);
            input = zero_link;
        } 
        
        num_copy = last_link(input);
        while(1) {
            if(num_copy->prev == NULL || num_copy->d != '0') break;
            LINK save = num_copy->prev;
            del_link(num_copy);
            num_copy = save;
        }

        if(!zero) ans = copy_link(input);
        
        else {
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
    if(anslen > point) {
        num_copy = ans;
        save = ans;
        if(positive) ans = char_to_list('+');
        else ans = char_to_list('-');

        for(; num_copy!=NULL; num_copy = num_copy->next) { insert(ans,num_copy->d); }
        free_all(save);

        num_copy = last_link(ans);
        while(point--) num_copy = num_copy->prev;
        insert(num_copy, '.');
    } else {
        num_copy = ans;
        if(positive) ans = char_to_list('+');
        else ans = char_to_list('-');
        save = ans;        
        insert(save,'0'); save = save->next; insert(save,'.'); save = save->next;
        point-=anslen;
        while(point--){
            insert(save,'0');
            save = save->next;
        }
        for(; num_copy!=NULL; num_copy = num_copy->next) {
            insert(save,num_copy->d);
        }
    }
    zero_erase(ans);
    free_all(num1);     free_all(num2);
    free_all(num1_int); free_all(num2_int);
    return ans;
}

// 계산
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
