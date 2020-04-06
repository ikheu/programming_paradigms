
/* 原型的存在是为了让调用者和被调用者关于 savedPC 上的活动布局达成一致，函数的调用参数符合调用参数类型规定*/

#if 0
#include <stdlib.h> // 注释掉，gcc 编译告警，可正常链接后执行
#include <stdio.h>  // 注释掉，gcc 编译告警，可正常链接后执行
#include <assert.h> // 注释掉，链接告警

int main() {
    void* tmp = malloc(40);
    assert(tmp != NULL);
    printf("Yum\n");
    free(tmp);
    return 0;
}
#endif


#if 0 // 原型的参数比实际的多了
#include <stdio.h>
int strlen(char*, int); // 不加上这一句会报错。加上这句会告警，并且正常执行

int main() {
    int num = 65;
    int length = strlen((char*)&num, num);
    printf("lenght = %d\n", length);
    return 0;
}
#endif

#if 0 // 原型的参数比实际少了
int memcpy(void *v1);
int main() {
    int n = 17;
    int m = memcpy(&n);
}
#endif

#if 0 // Segmentation fault
int main() {
    int *p;
    int q = *p;
    return 0;
}
#endif


#if 0 // Segmentation fault
int main() {
    int *p;
    int q = *p;
    return 0;
}
#endif


#if 0 // bus error，未模拟出来
int main() {
    char s[] = "hello";
    void* vp = s+1;
    *(short*)vp = 10;
    printf("%d\n", vp);
    return 0;
}
#endif


#if 0 // bus error，未模拟出来，同样未模拟出来，参考https://www.cnblogs.com/QingCHOW/p/4603162.html
int main() {
    union {
        char a[10];
        int i;
    } u;
    int *p = (int *) & (u.a[1]);
    *p = 17;
}
#endif

#if 0 // dead loop， the reason is very clear

#include <stdio.h>

int main() {
    int i;
    int arr[3];
    for (i = 0; i < 4; i++) {
        arr[i] = 0;
        printf("%d\n", i);
    }
    return 0;
}
#endif

#if 0 // 是否会死循环与大小尾有关，大尾不会小尾会

#include <stdio.h>

int main() {
    int i;
    short arr[3];
    for (i = 0; i < 4; i++) {
        arr[i] = 0;
        printf("%d\n", i);
    }
    return 0;
}
#endif


#if 1 // 模拟不出来死循环，savedPc不与arr相邻

#include <stdio.h>

int foo() {
    int arr[4];
    int i;
    for (i = 0; i <= 4; i++) {
        arr[i] -= 4;
    }
    return 0;
}

int main() {
    printf("hi\n");
    foo();
}
#endif
