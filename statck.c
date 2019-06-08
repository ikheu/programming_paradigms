#include <srdlib.h>
#include <string.h>
#include "stack.h"


void StackNew(stack *s, int elemSize) {

    s -> elemSize = elemSize;
    s -> logLength = 0;
    s -> allocLength = 4;
    s -> elems = malloc(4 * elemSize);
    assert(s -> elems != NULL);
}


void StackDispose(stack *s) {
    free(s -> elems);
}


void StackPush(stack *s, void *elemAddr) {
    if (s -> logLength == s -> allocLength) {
        StackGrow(s);
    }
    void *target = (char *) s -> elems + s -> logLength * s-> elemSize;
    memcpy(target, elemAddr, s -> elemSize);
    s -> logLength++;
}


static void StackGrow(stack *s) {
    s -> allocLength *= 2;
    s -> elems = realloc(s -> elems, s -> allocLength * s->elemSize);
    assert(s -> elems != NULL);
}


void StackPop(stack *s, void *elemAddr) {
    assert(s -> logLength > 0);
    void *source = (char *) s -> elems + (s -> logLength - 1) * s -> elemSize;
    memcpy(elemAddr, source, s -> elemSize);
    s -> logLength--;
}


int main() {
    const char *friends = {"AL", "Bob", "Carl"};
    stack stringStack;
    StackNew(&stringStack, sizeof(char *)); 
}