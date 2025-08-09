// mparam.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//导入头文件//
typedef struct MParam {
	uint8_t row;
	uint8_t column;
	float** data;
}*Matrix;
//声明矩阵结构体//

Matrix create_mat(uint8_t row, uint8_t column) {
	if (row == 0 || column == 0) return NULL;

	Matrix m = (Matrix)malloc(sizeof(struct MParam));
	if (!m) return NULL;

	m->data = (float**)malloc(row * sizeof(float*));
	if (!m->data) { free(m); return NULL; }

	for (uint8_t i = 0; i < row; ++i) {
		m->data[i] = (float*)calloc(column, sizeof(float));
		if (!m->data[i]) {
			while (i--) free(m->data[i]);
			free(m->data);
			free(m);
			return NULL;
		}
	}

	m->row = row;
	m->column = column;
	return m;
}
void free_mat(Matrix m) {//释放矩阵函数//
	if (!m) return;
	for (uint8_t i = 0; i < m->row; ++i) {
		free(m->data[i]);
	}
	free(m->data);
	free(m);
	}

void print_mat(Matrix m) {
	if (!m) return;
	for (uint8_t i = 0; i < m->row; ++i) {
		for (uint8_t j = 0; j < m->column; ++j)
			printf("%8.4f ", m->data[i][j]);
		putchar('\n');
	}
}

int main(void) {
	uint8_t rows, columns;//定义行列变量//
	printf("请输入矩阵的行数与列数\n");
	scanf("%hhu%hhu", &rows, &columns);
	Matrix A = create_mat(rows, columns);//创建原矩阵//
	if (!A) return printf("原矩阵创建失败\n");
	printf("请输入矩阵元素\n");
	for (uint8_t i = 0; i < rows; ++i) {
		for (uint8_t j = 0; j < columns; ++j) {
			scanf("%f", &A->data[i][j]);
		}
	}
	printf("创建矩阵成功\n");
	Matrix B = create_mat(columns, rows);//创建转置矩阵//
	if (!B) return printf("转置矩阵创建失败\n");
	for (uint8_t i = 0; i < columns; ++i) {
		for (uint8_t j = 0; j < rows; ++j) {
			B->data[i][j] = A->data[j][i];
		}
	}
	printf("逆转矩阵创建成功\n");
	Matrix T = create_mat(rows, rows);//创建结果矩阵//
	if (!T) return printf("结果矩阵创建失败\n");
	for (uint8_t i = 0; i < rows; ++i) {
		for (uint8_t j = 0; j < rows; ++j) {
			T->data[i][j] = 0;//初始化为零//
			for (uint8_t k = 0; k < columns; ++k) {
				T->data[i][j] += A->data[i][k] * B->data[k][j];//矩阵相乘//
			}
		}
	}
	printf("结果矩阵创建成功\n");
	printf("A × Aᵀ = \n");
	print_mat(T);
	free_mat(A);
	free_mat(B);
	free_mat(T);
	return 0;
}