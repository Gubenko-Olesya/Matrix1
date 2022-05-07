#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EPS 1e-8

double fabs (double a) {				//Gubenko Olesya 112
	return a > 0 ? a : -a;
}



//funksiya zapolnyaet matritsu zadannogo razmera size chislami
int randomize(double *A, int size) 			//Gubenko Olesya 112
{
	int i, j;
	srand(time(NULL));
	for(i = 0; i < size; i++) {
		for (j = 0; j < size; j++)
			A[i * size + j]=(double)(rand() % 201 - 100) / 100;
	}
	return 0;
}



//funksiya kopiruet matritsu
int copy(double *A, double *idA, int size)		//Gubenko Olesya 112
{
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j ++)
			idA[i * size + j] = A[i * size + j];
	}
	return 0;
}



//funksiya generiruet edinichnuyu matritsu
int identity(double *B, int size)			//Gubenko Olesya 112
{
	int i, j;
	for(i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (j == i)
				B[i * size + j] = 1;
			else
				B[i * size + j] = 0;
		}
	}
	return 0;
}



//funksiya obmenivaet dve stroki mestami
int swap(double *C, int size, int a, int b)		//Gubenko Olesya 112
{
	double k;
	int j;
	for (j = 0; j < size; j++) {
		k = C[a * size + j];
		C[a * size + j] = C[b * size + j];
		C[b * size + j] = k;
	}
	return 0;
}



//funksiya umnozhaet stroku matritsi na chislo
int plus(double *C, int size, int a, int b, double k)	//Gubenko Olesya 112
{
	int j;
	for (j = 0; j < size; j++)
		C[b * size + j]+=k * C[a * size + j];
	return 0;
}



//funksiua ishet lidera stroki
int zero(double *A, int size, int n1, int m1)		//Gubenko Olesya 112
{
	int i;
	for (i = n1; i < size; i++) {
		if(A[i * size + m1] != 0)
			return i;
	}
	return -1;
}



//eta i sleduyushaya funksii privodyat matritsu k verkhnetreugolnomu vidu
int fun(double *A, double *B, int size, int n1, int m1)	//Gubenko Olesya 112
{
	int i, k;
	k = zero (A, size, n1, m1);
	if (k == -1)
		return -1;
	swap(A, size, k, n1);
	swap(B, size, k, n1);
	for (i = n1 + 1; i < size; i++) {
		plus(B, size, n1, i, (-1) * A[i * size + m1] / A[n1 * size + m1]);
		plus(A, size, n1, i, (-1) * A[i * size + m1] / A[n1 * size + m1]);
	}
	return 1;
}



int funct(double *A, double *B, int size)		//Gubenko Olesya 112
{
	int n1 = 0, m1 = 0;
	while ((n1 < size) && (m1 < size)) {
		if(fun(A, B, size, n1, m1) == -1)
			m1++;
		else
			m1++;
			n1++;
	}
	return 0;
}



//funksiya ishet obratnuyu matritsu k dannoi matritse
int find_inverse(double *A, double *B, int size, int *Error) 	//Gubenko Olesya 112
{
	int i, j, k;
	*Error = 0;
	funct(A, B, size);

	/*
	for (j = 0; j < size; j++) {
		for (i = 0; i< size; i++)
			printf("%lf ", A[j * size + i]);
		printf("\n");
	}*/


	//proverka nevirojdennosti
	for (j = 0; j < size; j++) {
		if (A[j * size + j] == 0) {
			*Error = 1;
			return -1;
		}
	}

	//privodim A k diagonalnomu vidu
	for (j = 0; j < size; j++) {
		for(i = 0; i < j; i++) {
			plus(B, size, j, i, (-1) * A[i * size + j] / A[j * size + j]);
			plus(A, size, j, i, (-1) * A[i * size + j] / A[j * size + j]);
		}
	}
	//A = E
	for (i = 0; i < size; i++)	{
		for (k = 0; k < size; k++)
			B[i * size + k]/=A[i * size + i];
		A[i * size + i] = 1;
	}
	return 0;
}



//funksiya peremnozaet dannuyu matritsu s naidennoi i proveryaet, poluchilas li edinichnaya
int check(double *A, double *B, int size)			//Gubenko Olesya 112
{
	int i, j, k;
	double *C;
	C=(double*)malloc(size*size*sizeof(double));
	//peremnozhaem matritsy
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			C[i * size + j] = 0;
			for(k = 0; k < size; k++)
				C[i * size + j] += A[i * size + k] * B[k * size + j];
		}
	}
	//proveryaem, chto na glavnoi diagonali edinitsy, a vne ee nuli
	for (j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			if (i != j) {
				if (fabs(C[j * size + i]) > EPS) {
					printf ("cringe\n");
					return -1;
				}
			}
			if (i == j) {
				if (fabs(C[j * size + i]-1) > EPS)
					return -1;
			}
		}
	}
	return 0;
}

