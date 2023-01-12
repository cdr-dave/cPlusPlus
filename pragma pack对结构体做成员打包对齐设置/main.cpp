#include <stdio.h>
#include <stdalign.h>

#pragma pack(2)
typedef struct S1
{
    char c; //2
    int i; //4
} S1;

#pragma pack(push, 1)
typedef struct S2
{
    char c; // 1
    int i; //4
} S2;

typedef struct S3
{
    char c; // 1
    long long ll; //8
} S3;

// 恢复为之前pack设置 之前是指 #pragma pack(2)
#pragma pack(pop)

typedef struct S4
{
    char c; // 2
    long long ll; // 8
} S4;

// 恢复为当前编译器默认的pack设置
#pragma pack()

typedef struct S5
{
    char c; // 4
    int i; // 4
} S5;

typedef struct S6
{
    char c; // 8
    long long i; // 8
} S6;

int main(void)
{
        // 输出：S1 size: 6, alignment: 2, c offset: 0, i offset: 2
        printf("S1 size: %zu, alignment: %zu\n",
            sizeof(S1), alignof(S1));
    
        // 输出：S2 size: 5, alignment: 1, c offset: 0, i offset: 1
        printf("S2 size: %zu, alignment: %zu\n",
            sizeof(S2), alignof(S2));
    
        // 输出：S3 size: 9, alignment: 1, c offset: 0, i offset: 1
        printf("S3 size: %zu, alignment: %zu\n",
            sizeof(S3), alignof(S3));
    
        // 输出：S4 size: 10, alignment: 2, c offset: 0, i offset: 2
        printf("S4 size: %zu, alignment: %zu\n",
            sizeof(S4), alignof(S4));
    
        // 输出：S5 size: 8, alignment: 4, c offset: 0, i offset: 4
        printf("S5 size: %zu, alignment: %zu\n",
            sizeof(S5), alignof(S5));
    
    // 输出：S5 size: 16, alignment: 8
    printf("S5 size: %zu, alignment: %zu\n",
        sizeof(S6), alignof(S6));
    
//    // 输出：S1 size: 6, alignment: 2, c offset: 0, i offset: 2
//    printf("S1 size: %zu, alignment: %zu, c offset: %zu, i offset: %zu\n",
//        sizeof(S1), alignof(S1), offsetof(S1, c), offsetof(S1, i));
//
//    // 输出：S2 size: 5, alignment: 1, c offset: 0, i offset: 1
//    printf("S2 size: %zu, alignment: %zu, c offset: %zu, i offset: %zu\n",
//        sizeof(S2), alignof(S2), offsetof(S2, c), offsetof(S2, i));
//
//    // 输出：S3 size: 9, alignment: 1, c offset: 0, i offset: 1
//    printf("S3 size: %zu, alignment: %zu, c offset: %zu, i offset: %zu\n",
//        sizeof(S3), alignof(S3), offsetof(S3, c), offsetof(S3, ll));
//
//    // 输出：S4 size: 10, alignment: 2, c offset: 0, i offset: 2
//    printf("S4 size: %zu, alignment: %zu, c offset: %zu, i offset: %zu\n",
//        sizeof(S4), alignof(S4), offsetof(S4, c), offsetof(S4, ll));
//
//    // 输出：S5 size: 8, alignment: 4, c offset: 0, i offset: 4
//    printf("S5 size: %zu, alignment: %zu, c offset: %zu, i offset: %zu\n",
//        sizeof(S5), alignof(S5), offsetof(S5, c), offsetof(S5, i));
}
