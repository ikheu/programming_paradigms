#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void swap_base(int *ap, int *bp) {
    int tmp = *ap;
    *ap = *bp;
    *bp = tmp;
}

void swap_fail(void* ap, void* bp) {
    /*
        无法定义 void 类型的变量；无法对 void* 进行解引
        void tmp = *ap;
        *ap = *bp;
        *bp = tmp;
    */
}

void swap_v1(void* ap, void* bp, int size) {
   char buffer[size]; //编译器需要支持这种数组定义，当然也可以使用 malloc
   memcpy(buffer, ap, size); 
   memcpy(ap, bp, size);
   memcpy(bp, buffer, size);
}

void swap_v2(void* ap, void* bp, int size) {
    int i;
    char tmp;
    for (i=0; i < size; i++) {
        tmp = *(char*)(ap+i);
        *(char*)(ap+i) = *(char*)(bp+i);
        *(char*)(bp+i) = tmp;
    }
}

int test_swap() {
    int a = 10, b = 20;
    double d1 = 2.3, d2 = 3.4;
    char* s1 = "hello";
    char* s2 = "hi";
    swap_v1(&a, &b, sizeof(int));
    swap_v2(&d1, &d2, sizeof(double));
    swap_v2(&s1, &s2, sizeof(char*));
    printf("%d, %d\n", a, b);
    printf("%lf, %lf\n", d1, d2);
    printf("%s, %s\n", s1, s2);
    return 0;
}

int search_base(int key, int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

void* search(void* key, void* base, int n, int elemSize) {
    int i;
    for (i = 0; i < n; i++) {
        void* elemAddr = (char*) base + i * elemSize;
        if (memcmp(key, elemAddr, elemSize) == 0) {
            return elemAddr;
        }
    }
    return NULL;
}

int main() {
    int target = 3;
    int arr[] = {1,2,3};
    int* index;
    index = (int*) search(&target, arr, 3, sizeof(int));
    if (index != NULL) 
        printf("%d\n", *index);
    else
        printf("not found");
}
