#define InitStack(STACK)    (STACK)->top = NULL

typedef struct Node{
    LINK data;
    struct Node *next;
}Node;

typedef struct Stack{
    Node *top;
}Stack;

bool IsEmpty(Stack *stack){
    return stack->top == NULL;
}

void Push(Stack *stack, LINK head){
    Node *now= (Node*)malloc(sizeof(Node));
    now->data = head; 
    now->next = stack->top;
    stack->top = now;
}

LINK Pop(Stack *stack){
    Node *now;
    LINK re;
    if(IsEmpty(stack)) return NULL;
    now = stack->top;
    re = now->data;

    stack->top = now->next;
    return re;
}

LINK Top(Stack *stack){
    return stack->top->data;
}

void stack_reset(Stack *stack){
    Node *now = stack->top;
    while(now != NULL){
        Node *next = now->next;
        free(now);
        now = next;
    }
}
