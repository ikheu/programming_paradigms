#include <stdio.h>
#include <string.h>

void test_base0() {
    double pi = 3.14;
    char c = *(char *)&pi;
    printf("%c\n", c);
}

void test_base1() {
    char c = '1';
    double d = *(double *)&c;
    printf("%.6f\n", d);
}

struct fraction {
    int num;
    int denum;
};

int test_struct() {
    struct fraction pi;
    struct fraction *p;
    p = &pi;
    pi.num = 22;
    pi.denum = 7;
    ((struct fraction*)&(pi.denum))->num = 12;
    printf("%d\n", pi.denum);
    printf("%d\n", p->denum);
    printf("%d\n", p[0].num);
}

int test_arr() {
    int arr[5];
    arr[3] = 1;
    ((short*)arr)[7] = 1; 
    printf("%d\n", arr[3]); // 65537 == 2**16 + 1
}

struct student { // 16 bytes
    char *name;
    char suid[8];
    int numVisit;
};

int struct_with_arr() {
    struct student s[4];
    s[0].numVisit = 21;
    s[1].name = strdup("Tom");
    s[2].name = strdup("Adam"); /* 动态分配内存 */
    s[3].name = s[0].suid + 6;
    strcpy(s[1].suid, "40415xx"); /* 拷贝到 \0 为止 */
    strcpy(s[3].name, "12345");
    printf("%s\n", s[1].name);
    printf("%s\n", s[2].name);
    printf("%s\n", s[3].name);
}

int test_struct1(struct fraction* f) {
    f->num = 10;
    return 0;
}

int main() {
    test_struct();
    test_arr();
    struct_with_arr();
    return 0;
}
