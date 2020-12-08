LINK plus(LINK a, LINK b) {

    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    bool positive;
    unsigned long long point_count = 0;
    char now = 0;
    char up = 0;

    if(compare(a,b) == 2){
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
