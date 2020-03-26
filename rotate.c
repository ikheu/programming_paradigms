#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void rotate(void* start, void* middle, void* end) {
    int front_size = (char*) middle - (char*) start;
    int back_size = (char*) end - (char*) middle;
    char buffer[front_size];
    memcpy(buffer, start, front_size); /* 注意 memcpy 与 memmove 的区别 */
    memmove(start, middle, back_size);
    memcpy(middle, buffer, front_size);
}

int main() {
    char s[] = "hello";
    rotate(s, s+2, s+4);
    printf("%s\n", s);
}
