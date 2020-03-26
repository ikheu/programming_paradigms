typedef struct {
    void *elems; /* 栈开始位置 若是char*会不会更简单点?*/
    int elemSize; /* 栈元素大小 */
    int logLength; /* 使用的空间 */
    int allocLength; /* 分配的空间 */
    void (*freefn)(void*); /*栈上的元素涉及动态分配时，使用freefn*/
} stack; 

void StackNew(stack *s, int elemSize, void (*freefn)(void*));
void StackDispose(stack *s);
void StackPush(stack *s, void *elemAddr);
void StatckPop(stack *s, void *elemAddr);
