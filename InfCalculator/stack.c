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
    if(IsEmpty(stack)) return NULL; //
    now = stack->top;
    re = now->data;

    stack->top = now->next;
    return re;
}

//
LINK Top(Stack *stack){
    return stack->top->data;
}

//
void stack_reset(Stack *stack){
    Node *now = stack->top;
    while(now != NULL){ //
        Node *next = now->next;
        free(now);
        now = next;
    }
}
