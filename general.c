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

int lsearch_base(int key, int array[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

void* lsearch(void* key, void* base, int n, int elemSize) {
    int i;
    for (i = 0; i < n; i++) {
        void* elemAddr = (char*) base + i * elemSize;
        if (memcmp(key, elemAddr, elemSize) == 0) {
            return elemAddr;
        }
    }
    return NULL;
}

void* lsearch_v1(void* key, void* base, 
                    int n, int elemSize,
                    int (*cmpfun)(void*, void*)) {
    int i;
    for (i = 0; i < n; i++) {
        void* elemAddr = (char*) base + i * elemSize;
        if (cmpfun(key, elemAddr) == 0) {
            return elemAddr;
        }
    }
    return NULL;
}

int intcmp(void* ele1, void* ele2) {
    int* ip1 = ele1;
    int* ip2 = ele2;
    return *ip1 - *ip2;
}

int strcmp1(void *ele1, void* ele2) {
    return strcmp(ele1, *(char**)ele2);
}

int test_lsearch() {
    int target = 3;
    int arr[] = {1,2,3};
    int* index;
    index = (int*) lsearch(&target, arr, 3, sizeof(int));
    if (index != NULL) 
        printf("%d\n", *index);
    else
        printf("not found");
}

int test_lsearch_v1() {
    int target = 3;
    int arr[] = {1,2,3};
    int* index;
    char* names[] = {"Bob", "Tom", "Alice"};
    char* he = "Tom";
    char* targetUser;
    index = (int*) lsearch_v1(&target, arr, 3, sizeof(int), intcmp);
    if (index != NULL) 
        printf("%d\n", *index);
    else
        printf("not found");
    targetUser = lsearch_v1(he, names, 3, sizeof(char*), (int (*)(void *, void *))strcmp1);
    if (targetUser != NULL) 
        printf("%s\n", *(char**)targetUser);
    else
        printf("not found");


    // printf("%d\n", strcmp1(he, names[1]));
    
}


int main() {
    test_lsearch_v1();
    return 0;
}