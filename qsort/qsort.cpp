// qsort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int cmp_f(const void* a, const void* b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa > fb) - (fa < fb);//返回1，-1，0//
}

int main(void)
{
    float* arr = NULL;
    size_t m = 0, len = 0;
    float a;
    printf("请输入任意个数的浮点数，输入非数字结束输入:\n");
    while (scanf("%f", &a) == 1) {
        if (len == m) {
            m = m ? m * 2 : 1; //若m为零，则将其设为一，否则翻倍//
            float* t = (float*)realloc(arr, m * sizeof(float));
            if (!t) {
                perror("realloc");
                free(arr);
                return 1;
            }
            arr = t;
        }
        arr[len++] = a; //将输入的浮点数输入数组//    
    }
    if (len == 0) {
        printf("没有输入任何浮点数。\n");
        free(arr);
        return 0;
    }
    qsort(arr, len, sizeof(float), cmp_f);//对数组进行排序//
    printf("排序之后的浮点数为:\n");
    for (int i = 0; i < len; ++i) {
        printf("%.2f\n", arr[i]);
    }
    free(arr);//释放内存//
    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
