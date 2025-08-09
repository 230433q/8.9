// float and char.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef uint16_t fp_16_t;
// 把float转换为fp16//

static inline fp_16_t f_to_fp(float x) {
	union {float f; uint32_t u;} v = { x };//用联合体访问float的二进制//
	uint32_t u = v.u;
	uint32_t sign = (u >> 16) & 0x8000;
	uint32_t exp = (u >> 23) & 0xFF;
	uint32_t frac = u & 0x7FFFFF;//获取符号位、指数和尾数//
	if (exp == 255) return sign | 0x7C00;
	if (exp > 142) return fp_16_t (sign | 0x7C00);//若指数等于255或大于142，则返回inf或NaN//
	if (exp < 113) return sign;// 若指数小于113，则返回0//
	exp -= 112; //将指数转化为fp16的指数//
	uint16_t mant = (frac >> 13) + ((frac >> 12) & 1);
	return sign | (exp << 10) | mant;// 返回fp16的值//
}   

static inline float fp_to_f(fp_16_t x) {
	uint16_t sign = (x & 0x8000) << 16;
	uint16_t exp = (x & 0x7C00) >> 10;
	uint16_t frac = (x & 0x3FF);//获取符号位、指数和尾数//
	uint32_t u;
	if (exp == 0) {                               //若指数为0，则表示为0或非规格化数//
		if (frac == 0) u = sign;                  
		else {                                    //非规格化数的处理//
			exp = 127 - 14;
			while (!(frac & 0x0400)) { frac <<= 1; --exp; }
			frac &= 0x03FF;
			u = sign | (exp << 23) | (frac << 13);
		}
	}
	else if (exp == 31) {                       //若指数为31，则表示为inf或NaN//
		u = sign | 0x7F800000 | (frac << 13);
	}
	else {                                      //若为其他情况，则表示为规格化数//
		u = sign | ((exp + 112) << 23) | (frac << 13);
	}
	union { uint32_t u; float f; } v = { u };// 用联合体访问uint32_t的二进制//
	return v.f; //返回float的值//
}

int main(void) {
	float f1 = 59.622f, f2 = 92.6327f;
	uint16_t fp1 = f_to_fp(f1), fp2 = f_to_fp(f2);//将float转化为fp16//
	char a[4];
	uint16_t fp3, fp4;
	memcpy(a, &fp1, sizeof fp1);
	memcpy(a + 2, &fp2, sizeof fp2);//将fp16的值存入字符数组a[4]中/
	memcpy(&fp3, a, sizeof fp1);
	memcpy(&fp4, a + 2, sizeof fp2);//将fp16的值取出//
	float f3 = fp_to_f(fp3), f4 = fp_to_f(fp4);//将fp16转化回去//
	printf("f1:%f,f2:%f\n", f1, f2);
	printf("f3:%f,f4:%f\n", f3, f4);
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
