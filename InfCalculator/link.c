typedef char DATA;

struct linked_list {
    DATA d;
    struct linked_list *prev, *next;
};

typedef struct linked_list ELEMENT;
typedef ELEMENT *LINK;

LINK char_to_list(char s) {
    LINK head;
    head = malloc(sizeof(ELEMENT));
    head->d = s;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

unsigned long long count(LINK head) {
    unsigned long long c = 0;
    while(head != NULL) {
        head = head->next;
        c++;
    }
    
    return c;
}

LINK last_link(LINK head) {
    while(head->next != NULL) head = head->next;
    return head;
}

void del_link(LINK p) {
    if(p->next == NULL) {
        p->prev->next = NULL;
        free(p);
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
    }
}

void zero_erase(LINK head) {
    head = last_link(head);
    while(head->d!='.' && head->d=='0') {
        LINK store = head->prev;
        del_link(head);
        head = store;
    }
}

void concatenate(LINK a, LINK b) {
    if(a->next == NULL) {
        a->next = b;
        b->prev = a;
    } else {
        concatenate(a->next,b);
    }
}

void insert(LINK p1, char x) {
    LINK q = char_to_list(x);
    if(p1->next == NULL) {
        p1->next = q; q->prev = p1;
    } else {
        q->next = p1->next; p1->next->prev = q;
        p1->next = q; q->prev = p1;
    }
}

LINK copy_link(LINK p2) {
    LINK p1 = char_to_list(p2->d);
    LINK p = p1;
    p2 = p2->next;
    while(p2!=NULL) {
        insert(p,p2->d);
        p = p->next;
        p2=p2->next;
    }
    return p1;
}

char compare(LINK x, LINK y) {
    LINK a = x->next;
    LINK b = y->next;
    while((a!=NULL && b!=NULL) && (a->d!='.' || b->d!='.')) {
        if(a->d == '.') return 2;
        if(b->d == '.') return 1;
        a = a->next;
        b = b->next;
    }

    a = x->next;
    b = y->next;
    while(a!=NULL && b!=NULL) {
        if(a==NULL) return 2;
        if(b==NULL) return 1;
        if(a->d > b->d) return 1;
        if(a->d < b->d) return 2;
        a = a->next;
        b = b->next;
    }
    return 3;
}

LINK Upzero_fill(LINK x, LINK y) {
    LINK a = x;
    LINK b = y;

    unsigned long long alen = 0, blen = 0;
    for(; a->d != '.'; a=a->next) alen++;
    for(; b->d != '.'; b=b->next) blen++;

    if(alen == blen) return y;
    
    unsigned long long len = alen - blen;
    LINK zero = char_to_list('0');
    while(len-->0) insert(zero,'0');
    concatenate(zero,y);
    return zero;
}

void Downzero_fill(LINK x, LINK y){
    LINK a = last_link(x);
    LINK b = last_link(y);
    for(; a->d != '.'; a=a->prev);
    for(; b->d != '.'; b=b->prev);
    while(a!=NULL || b!=NULL){
        if(a->next != NULL && b->next == NULL) insert(b,'0');
        if(a->next == NULL && b->next != NULL) insert(a,'0');
        a=a->next; b=b->next;
    }
}

// 메모리 해제
void free_all(LINK h){
    if(h == NULL) return;
    free_all(h->next);
    free(h);
}

// 링크 보기 좋게 출력
void print_link(LINK h) {
    if(h->d == '+') h = h->next;
    for(;h != NULL; h = h->next) {
        if(h->d == '.') {
            if(h->next == NULL) {
                break;
            } else if (h->next->d < '0' || h->next->d > '9') {
                continue;
            }
        }
        printf("%c", h->d);
    }
}
