//스택 탑에 NULL로 초기화
#define InitStack(STACK)    (STACK)->top = NULL

//노드 정의
typedef struct Node{
    LINK data;
    struct Node *next;
}Node;

//스택 정의
typedef struct Stack{
    Node *top;
}Stack;

//스택 탑이 가리키는 것이 있는지 없는지 리턴
bool IsEmpty(Stack *stack){
    return stack->top == NULL;
}

//헤드를 스택 탑으로 푸시
void Push(Stack *stack, LINK head){
    Node *now= (Node*)malloc(sizeof(Node)); //now의 메모리를 노드크기로 동적할당
    now->data = head; 
    now->next = stack->top;
    stack->top = now;
}

//스택 탑을 팝
LINK Pop(Stack *stack){
    Node *now;
    LINK re;
    //스택이 비었으면 NULL반환
    //비어있지 않으면 now의 값을 빈환
    if(IsEmpty(stack)) return NULL;
    now = stack->top;
    re = now->data;

    stack->top = now->next;
    return re;
}

//스택 탑의 데이터를 반환
LINK Top(Stack *stack){
    return stack->top->data;
}

//스택을 해제
void stack_reset(Stack *stack){
    Node *now = stack->top;
    //now가 가리키는 곳이 NULL이 될때까지 노드를 할당해제
    while(now != NULL){
        Node *next = now->next;
        free(now);
        now = next;
    }
}
