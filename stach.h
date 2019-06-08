typedef struct {
    void *elems;
    int elemSize;
    int logLength;
    int allocLength;
} stack;

void StackNew(stack *s, int elemSize);
void StackDispose(stack *s);
void StackPush(stack *s, void *elemAddr);
void StatckPop(stack *s, void *elemAddr);
