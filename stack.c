#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h> /* assert */
#include "stack.h"


void StackNew(stack *s, int elemSize, void (*freefn)(void*)) {
    assert(elemSize > 0); 
    s->elemSize = elemSize;
    s->logLength = 0;
    s->allocLength = 4;
    s->elems = malloc(4 * elemSize);
    s->freefn = freefn;
    assert(s->elems != NULL);
}

void StackDispose(stack *s) {
    int i;
    if (s->freefn != NULL) {
        for (i = 0; i< s->logLength; i++) {
            s->freefn((char*)s->elems + i * s->elemSize);
        }
    }
    free(s -> elems);
}

static void StackGrow(stack *s) {
    s->allocLength *= 2;
    s->elems = realloc(s->elems, s->allocLength * s->elemSize);
    assert(s->elems != NULL);
}

void StackPush(stack *s, void *elemAddr) {
    if (s->logLength == s->allocLength) {
        StackGrow(s);
    }
    void *target = (char*) s->elems + s->logLength * s->elemSize;
    memcpy(target, elemAddr, s -> elemSize);
    s->logLength++;
}

void StackPop(stack *s, void *elemAddr) {
    assert(s->logLength > 0);
    void *source = (char*) s->elems + (s->logLength - 1) * s->elemSize;
    memcpy(elemAddr, source, s->elemSize);
    s->logLength--;
}
void stringFree(void* elem) {
    char * target = *(char**)elem;
    free(target);
}

int main() {
    int i;
    const char *friends[] = {"AL", "Bob", "Carl"};
    stack stringStack;
    StackNew(&stringStack, sizeof(char *), stringFree);
    for (i = 0; i < 3; i++) {
        char *copy = strdup(friends[i]);
        StackPush(&stringStack, &copy);
    }
    for(i = 0; i < 3; i++) {
        char *target;
        StackPop(&stringStack, &target);
        printf("%s\n", target);
    }
    StackDispose(&stringStack);
}
