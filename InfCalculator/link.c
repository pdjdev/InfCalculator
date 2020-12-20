typedef char DATA;

// struct 구조체를 사용하여 linked_list 요소 정의하기
struct linked_list {
    DATA d;
    struct linked_list *prev, *next;
};

typedef struct linked_list ELEMENT;
typedef ELEMENT *LINK;

// 노드 생성
LINK char_to_list(char s) {
    LINK head;
    head = malloc(sizeof(ELEMENT));
    head->d = s;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

// DLL의 길이 구하기
unsigned long long count(LINK head) {
    unsigned long long c = 0; //부호가 없는 8 바이트의 정수형 변수 
    while(head != NULL) {
        head = head->next;
        c++;
    }
    
    return c;
}

// DLL의 마지막 노드 반환
LINK last_link(LINK head) {
    while(head->next != NULL) head = head->next;
    return head;
}

// 입력받은 노드 p를 DLL에서 삭제
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

// DLL 끝쪽의 '0' 삭제
void zero_erase(LINK head) {
    head = last_link(head);
    while(head->d!='.' && head->d=='0') {
        LINK store = head->prev;
        del_link(head);
        head = store;
    }
}

// a DLL과 b DLL을 하나의 DLL로 연결하기
void concatenate(LINK a, LINK b) {
    if(a->next == NULL) {
        a->next = b;
        b->prev = a;
    } else {
        concatenate(a->next,b);
    }
}

// p1 DLL의 노드 p1뒤에 x를 가지는 노드 삽입
void insert(LINK p1, char x) {
    LINK q = char_to_list(x);
    if(p1->next == NULL) {
        p1->next = q; q->prev = p1;
    } else {
        q->next = p1->next; p1->next->prev = q;
        p1->next = q; q->prev = p1;
    }
}

// p2 DLL을 복사한 DLL 생성
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

// X DLL과 Y DLL의 크기 비교
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

//DLL x와 y의 길이 맞추기
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

//DLL x와 y의 소수점 아래 자릿수 
void Downzero_fill(LINK x, LINK y) {
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
