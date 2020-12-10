typedef char DATA;

struct linked_list {
    DATA d;
    struct linked_list *prev, *next;
};

typedef struct linked_list ELEMENT;
typedef ELEMENT *LINK;
